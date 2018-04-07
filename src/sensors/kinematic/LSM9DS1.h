#ifndef GOOSE_SENSORS_LSM9DS1_H
#define GOOSE_SENSORS_LSM9DS1_H

#include "../../register/I2CRegister.h"

#define LSM9DS1_AG_ADDRESS 0x6b
//#define LSM9DS1_M_ADDRESS 0x1e

#define LSM9DS1_DEV_ID_XG 0x68
//#define LSM9DS1_DEV_ID_M  0x3d

namespace wlp {

    class LSM9DS1 {
    public:

        enum {
            INT1_CTRL = 0x0c,
            INT2_CTRL = 0x0d,
            DEV_ID_XG = 0x0f,
            CTRL_REG5_XL = 0x1f,
            CTRL_REG6_XL = 0x20,
            CTRL_REG7_XL = 0x21,
            CTRL_REG9 = 0x23,
            STATUS_REG_1 = 0x27,
            OUT_X_L_XL = 0x28,
            FIFO_CTRL = 0x2e,
            FIFO_SRC = 0x2f,

        } __attribute__((packed));

        enum {
            OFFSET_X_REG_L_M = 0x05,
            OFFSET_X_REG_H_M = 0x06,
            OFFSET_Y_REG_L_M = 0x07,
            OFFSET_Y_REG_H_M = 0x08,
            OFFSET_Z_REG_L_M = 0x09,
            OFFSET_Z_REG_H_M = 0x0a,
            DEV_ID_M = 0x0f,
            CTRL_REG1_M = 0x20,
            CTRL_REG2_M = 0x21,
            CTRL_REG3_M = 0x22,
            CTRL_REG4_M = 0x23,
            CTRL_REG5_M = 0x24,
            STATUS_REG_M = 0x27,
            OUT_X_L_M = 0x28,
            OUT_X_H_M = 0x29,
            OUT_Y_L_M = 0x2a,
            OUT_Y_H_M = 0x2b,
            OUT_Z_L_M = 0x2c,
            OUT_Z_H_M = 0x2d,
            INT_CFG_M = 0x30,
            INT_SRC_M = 0x31,
            INT_THS_L_M = 0x32,
            INT_THS_H_M = 0x33
        } __attribute__((packed));

        enum Axis{
            X, Y, Z, ALL
        } __attribute__((packed));

        enum AccelScale {
            a2G = 2,
            a4G = 4,
            a8G = 8,
            a16G = 16
        } __attribute__((packed));

        enum ODR {
            XL_POWER_DOWN,
            XL_ODR_10,
            XL_ODR_50,
            XL_ODR_119,
            XL_ODR_238,
            XL_ODR_476,
            XL_ODR_952
        } __attribute__((packed));

        enum ABW {
            A_ABW_408,
            A_ABW_211,
            A_ABW_105,
            A_ABW_50,
            A_ABW_AUTO
        } __attribute__((packed));

        enum InterruptSelect {
            XG_INT1 = INT1_CTRL,
            XG_INT2 = INT2_CTRL,
            INT_DRDY_XL = 1 << 0,
            INT_DRDY_G = 1 << 1,
            INT1_BOOT = 1 << 2,
            INT2_DRDY_TEMP = 1 << 2,
            INT_FTH = 1 << 3,
            INT_OVR = 1 << 4,
            INT_FSS5 = 1 << 5,
            INT_IG_XL = 1 << 6,
            INT1_IG_G = 1 << 7,
            INT2_INACT = 1 << 7
        } __attribute__((packed));

        enum InterruptGenerator {
            XLIE_XL = 1 << 0,
            XHIE_XL = 1 << 1,
            YLIE_XL = 1 << 2,
            YHIE_XL = 1 << 3,
            ZLIE_XL = 1 << 4,
            ZHIE_XL = 1 << 5,
            GEN_6D = 1 << 6
        } __attribute__((packed));

        enum HLActive {
            INT_ACTIVE_HIGH,
            INT_ACTIVE_LOW
        } __attribute__((packed));

        enum PPOD {
            INT_PUSH_PULL,
            INT_OPEN_DRAIN
        } __attribute__((packed));

        enum FIFOModeType {
            FIFO_OFF = 0,
            FIFO_THS = 1,
            FIFO_CONT_TRIGGER = 3,
            FIFO_OFF_TRIGGER = 4,
            FIFO_CONT = 5
        } __attribute__((packed));

        struct __attribute__((packed)) AccelSettings {
            bool enabled:1;
            bool enableX:1;
            bool enableY:1;
            bool enableZ:1;

            uint8_t scale:2;
            uint8_t sampleRate:6;
            uint8_t bandwidth=-1;
            uint8_t highResEnable=false;
            uint8_t highResBandwidth=0;

            //Valid valid range 0 <= bandwidth <= 3. If value is outside range,
            //the bandwidth is determined by the sample rate.

            /*uint8_t m_bandwidth : 3;

            bool m_high_res_enable : 1;
            uint8_t m_high_res_bandwidth : 2;*/

            AccelSettings(uint8_t scale, uint8_t sample_rate, uint8_t bandwidth);
        };

        AccelSettings accelSettings;

        int16_t ax, ay, az; //x,y,z readings of accelorometer

        float aBias[3];
        int16_t aBiasRaw[3];

        //begin() sets up the scale and output rate of each
        // sensor. Values set in the AccelSettings struct
        // will take affect after calling this function
        bool begin();

        void calibrate(bool autoCalc = true);

        bool accel_available();

        // read the accelerometer output registers
        //this function will read all six accelerometer output registers
        //readings are stored in the ax, ay, az, variables. Read those after calling accel_read()
        void accel_read();

        float accel_x();

        float accel_y();

        float accel_z();

        //convert from RAW signed 16-bit value to gravity (g's)
        float accel_calc(int16_t raw_accel);

        //input: the desired accel scale. Must be from AccelScale values
        void accel_set_scale(uint8_t aScl);

        // Set the output data rate of the accelerometer
        // Input:
        //	- aRate = The desired output rate of the accel.
        void accel_set_odr(uint8_t aRate);

        void enableFIFO(bool enable = true);

        // setFIFO() - Configure FIFO mode and Threshold
        void setFIFO(FIFOModeType fifoMode, uint8_t fifoThs);


        explicit LSM9DS1(
            uint8_t address_ag = LSM9DS1_AG_ADDRESS,
            uint8_t scale = AccelScale::a2G,
            uint8_t sample_rate = ODR::XL_ODR_952,
            uint8_t bandwidth = ABW::A_ABW_AUTO
        );

    protected:

        I2CRegister accel_register;

        float aRes;

        bool _autoCalc;

        void accel_init();

        void calcaRes();

        void constrainScales();

    private:
        //AccelSettings m_accel_settings;
        //I2CRegister m_register_m;
        //I2CRegister m_register_ag;

        /*double m_accel_res;
        int16_t m_accel_x;
        int16_t m_accel_y;
        int16_t m_accel_z; */
    };

}

#endif //GOOSE_SENSORS_LSM9DS1_H
