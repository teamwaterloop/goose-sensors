#ifndef GOOSE_SENSORS_LSM9DS1_H
#define GOOSE_SENSORS_LSM9DS1_H

#include <stdint-gcc.h>

#include <Cosa/TWI.hh>

#include "../Sensor.h"
#include "../../register/I2CRegister.h"

#define LSM9DS1_I2C_ADDRESS 0x6b
//#define LSM9DS1_I2C_ADDRESS 0x1e

#define LSM9DS1_DEV_ID_XG 0x68
//#define LSM9DS1_DEV_ID_M  0x3d

namespace wlp {

    class LSM9DS1 : public Sensor, public TWI::Driver {
    public:
        enum {
            ACT_THS = 0x04,
            ACT_DUR = 0x05,
            INT_GEN_CFG_XL = 0x06,
            INT_GEN_THS_X_XL = 0x07,
            INT_GEN_THS_Y_XL = 0x08,
            INT_GEN_THS_Z_XL = 0x09,
            INT_GEN_DUR_XL = 0x0a,
            REFERENCE_G = 0x0b,
            INT1_CTRL = 0x0c,
            INT2_CTRL = 0x0d,
            DEV_ID_XG = 0x0f,
            CTRL_REG1_G = 0x10,
            CTRL_REG2_G = 0x11,
            CTRL_REG3_G = 0x12,
            ORIENT_CFG_G = 0x13,
            INT_GEN_SRC_G = 0x14,
            OUT_TEMP_L = 0x15,
            OUT_TEMP_H = 0x16,
            STATUS_REG_0 = 0x17,
            OUT_X_L_G = 0x18,
            OUT_X_H_G = 0x19,
            OUT_Y_L_G = 0x1a,
            OUT_Y_H_G = 0x1b,
            OUT_Z_L_G = 0x1c,
            OUT_Z_H_G = 0x1d,
            CTRL_REG4 = 0x1e,
            CTRL_REG5_XL = 0x1f,
            CTRL_REG6_XL = 0x20,
            CTRL_REG7_XL = 0x21,
            CTRL_REG8 = 0x22,
            CTRL_REG9 = 0x23,
            CTRL_REG10 = 0x24,
            INT_GEN_SRC_XL = 0x26,
            STATUS_REG_1 = 0x27,
            OUT_X_L_XL = 0x28,
            OUT_X_H_XL = 0x29,
            OUT_Y_L_XL = 0x2a,
            OUT_Y_H_XL = 0x2b,
            OUT_Z_L_XL = 0x2c,
            OUT_Z_H_XL = 0x2d,
            FIFO_CTRL = 0x2e,
            FIFO_SRC = 0x2f,
            INT_GEN_CFG_G = 0x30,
            INT_GEN_THS_XH_G = 0x31,
            INT_GEN_THS_XL_G = 0x32,
            INT_GEN_THS_YH_G = 0x33,
            INT_GEN_THS_YL_G = 0x34,
            INT_GEN_THS_ZH_G = 0x35,
            INT_GEN_THS_ZL_G = 0x36,
            INT_GEN_DUR_G = 0x37
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

        enum Axis {
            X, Y, Z, ALL
        } __attribute__((packed));

        enum Scale {
            A_SCALE_2G,
            A_SCALE_16G,
            A_SCALE_4G,
            A_SCALE_8G
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
            A_ABW_50
        } __attribute__((packed));

        enum InterruptSelect {
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

        /*// TODO bit field parameters
        struct AccelSettings {
            uint8_t enabled;
            uint8_t scale;
            uint8_t sample_rate;
            uint8_t enable_x;
            uint8_t enable_y;
            uint8_t enable_z;
            uint8_t high_res_enabled;
            uint8_t high_res_bandwidth;

            int8_t bandwidth;
        };

        struct TemperatureSettings {
            uint8_t enabled;
        };

        struct IMUSettings {
            AccelSettings accel;
            TemperatureSettings temp;
        };*/

        struct __attribute__((packed)) Settings {
            enum {
                BANDWIDTH_AUTO = 7
            } __attribute__((packed));

            bool m_enabled : 1 = true;
            bool m_enable_x : 1 = true;
            bool m_enable_y : 1 = true;
            bool m_enable_z : 1 = true;

            uint8_t m_scale : 5;
            uint8_t m_sample_rate : 3;

            // Value values 0 <= bandwidth <= 3
            // If outside range, bandwidth determined by sample rate
            uint8_t m_bandwidth : 3;

            bool m_high_res_enable : 1 = false;
            uint8_t m_high_res_bandwidth : 2 = 0;

            Settings(uint8_t scale, uint8_t sample_rate, uint8_t bandwidth);
        };

        explicit LSM9DS1(
            uint8_t address = LSM9DS1_I2C_ADDRESS,
            uint8_t scale = LSM9DS1::Scale::A_SCALE_4G,
            uint8_t sample_rate = LSM9DS1::ODR::XL_ODR_952,
            uint8_t bandwidth = LSM9DS1::Settings::BANDWIDTH_AUTO
        );

        bool begin();

    protected:
        float read_value() override;

    private:
        Settings m_settings;
        I2CRegister m_register;
    };

}

#endif //GOOSE_SENSORS_LSM9DS1_H
