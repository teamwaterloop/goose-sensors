#include "LSM9DS1.h"
#include <Cosa/Trace.hh>

using namespace wlp;

#define SENSITIVITY_ACCELEROMETER_2  0.000061
#define SENSITIVITY_ACCELEROMETER_4  0.000122
#define SENSITIVITY_ACCELEROMETER_8  0.000244
#define SENSITIVITY_ACCELEROMETER_16 0.000732

LSM9DS1::AccelSettings::AccelSettings(uint8_t scale, uint8_t sample_rate, uint8_t bandwidth)
    : enabled(true),
    enableX(true),
    enableY(true),
    enableZ(true),
    // accel scale can be 2, 4, 8, or 16
    scale(2),
    sampleRate(sample_rate),
    bandwidth(bandwidth),
    highResEnable(false),
    highResBandwidth(0) {}

LSM9DS1::LSM9DS1(
    uint8_t address_ag,
    uint8_t scale,
    uint8_t sample_rate,
    uint8_t bandwidth)
    : accelSettings(scale, sample_rate, bandwidth),
    accel_register(address_ag){}


bool LSM9DS1::begin() {
    calcaRes();

    uint8_t dev_id_xg = accel_register.read8(LSM9DS1::DEV_ID_XG);

    if (dev_id_xg != LSM9DS1_DEV_ID_XG) {
        return false;
    }

    accel_init();

    return true;
}

void LSM9DS1::calcaRes(){
    switch ((unsigned int)accelSettings.scale) {
        case AccelScale::a2G:
            aRes = SENSITIVITY_ACCELEROMETER_2;
            break;
        case AccelScale::a4G:
            aRes = SENSITIVITY_ACCELEROMETER_4;
            break;
        case AccelScale::a8G:
            aRes = SENSITIVITY_ACCELEROMETER_8;
            break;
        case AccelScale::a16G:
            aRes = SENSITIVITY_ACCELEROMETER_16;
            break;
        default:
            break;
    }
}


void LSM9DS1::accel_init() {
    uint8_t t_reg_value = 0x0;
    if (accelSettings.enableX) {
        t_reg_value |= 1 << 3;
    }
    if (accelSettings.enableY) {
        t_reg_value |= 1 << 4;
    }
    if (accelSettings.enableZ) {
        t_reg_value |= 1 << 5;
    }
    accel_register.write8(CTRL_REG5_XL, t_reg_value);

    t_reg_value = 0;
    if (accelSettings.enabled) {
        t_reg_value |= (accelSettings.sampleRate & 0x07) << 5;
    }
    switch ((unsigned int)accelSettings.scale) {
        case AccelScale::a4G:
            t_reg_value |= 0x2 << 3;
            break;
        case AccelScale::a8G:
            t_reg_value |= 0x3 << 3;
            break;
        case AccelScale::a16G:
            t_reg_value |= 0x1 << 3;
            break;
        default:
            t_reg_value |= 0x0 << 3;
            break;
    }
    if (accelSettings.bandwidth < ABW::A_ABW_AUTO) {
        t_reg_value |= 1 << 2;
        t_reg_value |= (accelSettings.bandwidth & 0x03);
    }
    accel_register.write8(CTRL_REG6_XL, t_reg_value);

    t_reg_value = 0;
    if (accelSettings.highResEnable) {
        t_reg_value |= 1 << 7;
        t_reg_value |= (accelSettings.highResBandwidth & 0x03) << 5;
    }
    accel_register.write8(CTRL_REG7_XL, t_reg_value);
}


bool LSM9DS1::accel_available() {
    uint8_t status = accel_register.read8(STATUS_REG_1);
    return (status &(1<<0));
}

void LSM9DS1::accel_read() {
    uint8_t data[6];
    if (!accel_register.read_bytes<6>(OUT_X_L_XL, data)) {
        return;
    }
    // bytes are read backwards
    ax = (data[4] << 8) | data[5]; //store x-axis values into ax
    ay = (data[2] << 8) | data[3]; //store y-axis values into ay
    az = (data[0] << 8) | data[1]; //store z-axis values in az
    if(_autoCalc){
        ax -= aBiasRaw[X];
        ay -= aBiasRaw[Y];
        az -= aBiasRaw[Z];
    }
}

void LSM9DS1::calibrate(bool autoCalc)
{
    uint8_t data[6] = {0, 0, 0, 0, 0, 0};
    uint8_t samples = 0;
    int ii;
    int32_t aBiasRawTemp[3] = {0, 0, 0};

    // Turn on FIFO and set threshold to 32 samples
    enableFIFO(true);
    setFIFO(FIFO_THS, 0x1F);
    while (samples < 0x1F)
    {
        samples = (accel_register.read8(FIFO_SRC) & 0x3F); // Read number of stored samples
    }
    for(ii = 0; ii < samples ; ii++)
    {	// Read the gyro data stored in the FIFO
        accel_read();
        aBiasRawTemp[0] += ax;
        aBiasRawTemp[1] += ay;
        aBiasRawTemp[2] += az - (int16_t)(1./aRes); // Assumes sensor facing up!
    }
    for (ii = 0; ii < 3; ii++)
    {
        aBiasRaw[ii] = aBiasRawTemp[ii] / samples;
        aBias[ii] = accel_calc(aBiasRaw[ii]);
    }

    enableFIFO(false);
    setFIFO(FIFO_OFF, 0x00);

    if (autoCalc) _autoCalc = true;
}

void LSM9DS1::enableFIFO(bool enable){
    uint8_t temp = accel_register.read8(CTRL_REG9);
    if(enable) temp |= (1<<1);
    else temp &= ~(1<<1);
    accel_register.write8(CTRL_REG9, temp);
}

void LSM9DS1::setFIFO(FIFOModeType fifoMode, uint8_t fifoThs)
{
    // Limit threshold - 0x1F (31) is the maximum. If more than that was asked
    // limit it to the maximum.
    uint8_t threshold = fifoThs <= 0x1F ? fifoThs : 0x1F;
    accel_register.write_bytes(FIFO_CTRL, ((fifoMode & 0x7) << 5) | (threshold & 0x1F));
}

/*uint8_t LSM9DS1::getFIFOSamples()
{
    return (settings.device.agRegister.read8(FIFO_SRC) & 0x3F);
}*/

float LSM9DS1::accel_calc(int16_t raw_accel) {
    return static_cast<float>(aRes * raw_accel);
}

/*void LSM9DS1::accel_set_scale(uint8_t aScl){
    uint8_t tempRegValue= accel_register.read8(CTRL_REG6_XL);
    //mask out accel scale bits
    tempRegValue &= 0xE7;

    switch((unsigned int)aScl){
        case 4:
            tempRegValue |= (0x2 <<3);
            accelSettings.scale =4;
            break;
        case 8:
            tempRegValue |= (0x3 <<3);
            accelSettings.scale = 8;
            break;
        case 16:
            tempRegValue |= (0x1 <<3);
            accelSettings.scale=16;
            break;
        default:
            accelSettings.scale = 2;
            break;
    }
    accel_register.write8(CTRL_REG6_XL, tempRegValue);
    calcaRes();
}*/

/*void LSM9DS1::accel_set_odr(uint8_t aRate) {
    // Only do this if aRate is not 0 (which would disable the accel)
    if ((aRate & 0x07) != 0)
    {
        // We need to preserve the other bytes in CTRL_REG1_XM. So, first read it:
        uint8_t temp = accel_register.read8(CTRL_REG6_XL);
        // Then mask out the accel ODR bits:
        temp &= 0x1F;
        // Then shift in our new ODR bits:
        temp |= ((aRate & 0x07) << 5);
        accelSettings.sampleRate = aRate & 0x07;
        // And write the new register value back into CTRL_REG1_XM:
        accel_register.write8(CTRL_REG6_XL, temp);
    }
}*/

/*uint8_t LSM9DS1::accel_get_int_src()
{
    uint8_t intSrc = settings.device.xgAddress.read8(INT_GEN_SRC_XL);

    // Check if the IA_XL (interrupt active) bit is set
    if (intSrc & (1<<6))
    {
        return (intSrc & 0x3F);
    }

    return 0;
}*/

float LSM9DS1::accel_x() {
    return accel_calc(ax);
}

float LSM9DS1::accel_y() {
    return accel_calc(ay);
}

float LSM9DS1::accel_z() {
    return accel_calc(az);
}
