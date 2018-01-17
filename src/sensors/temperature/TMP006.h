#ifndef GOOSE_SENSORS_TMP006_H
#define GOOSE_SENSORS_TMP006_H

#define TMP006_I2C_ADDR 0x40

#define TMP006_MAN_ID 0x5449
#define TMP006_DEV_ID 0x67

#define TMP006_B0   (-2.94e-5)
#define TMP006_B1   (-5.7e-7)
#define TMP006_B2   (4.63e-9)
#define TMP006_C2   (13.4)
#define TMP006_TREF (298.15)
#define TMP006_A2   (-1.678e-5)
#define TMP006_A1   (1.75e-3)
#define TMP006_S0   (6.4) // * 10^-14

#include <Cosa/TWI.hh>

#include "../Sensor.h"
#include "../../register/I2CRegister.h"

namespace wlp {

    class TMP006 : public Sensor, public TWI::Driver {
    public:
        enum {
            VOBJ = 0x00,
            TAMB = 0x01,
            CONFIG = 0x02,
            MAN_ID = 0xfe,
            DEV_ID = 0xff,
        } __attribute__((packed));

        enum {
            CFG_DRDY = 0x0080,
            CFG_DRDYEN = 0x0100,
            CFG_MODEON = 0x7000,
            CFG_RESET = 0x8000
        } __attribute__((packed));

        enum {
            CFG_SAMPLE_1 = 0x0000,
            CFG_SAMPLE_2 = 0x0200,
            CFG_SAMPLE_4 = 0x0400,
            CFG_SAMPLE_8 = 0x0600,
            CFG_SAMPLE_16 = 0x0800
        } __attribute__((packed));

        enum {
            DIE, OBJECT, NUM_MODES
        } __attribute__((packed));

        explicit TMP006(
            uint8_t address = TMP006_I2C_ADDR,
            uint16_t sample_rate = TMP006::CFG_SAMPLE_16,
            uint8_t mode = TMP006::DIE
        );

        bool begin();

        void sleep();

        void wake();

        double read_die_temperature();

        double read_obj_temperature();

    protected:
        float read_value() override;

    private:
        int16_t read_raw_die_temperature();

        int16_t read_raw_voltage();

        uint8_t m_sample_rate;
        uint8_t m_mode;

        I2CRegister m_register;
    };

}

#endif //GOOSE_SENSORS_TMP006_H
