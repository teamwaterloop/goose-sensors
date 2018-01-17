#include "LSM9DS1.h"

#include <Cosa/Trace.hh>

using namespace wlp;

LSM9DS1::Settings::Settings(uint8_t scale, uint8_t sample_rate, uint8_t bandwidth)
    : m_scale(scale),
      m_sample_rate(sample_rate),
      m_bandwidth(bandwidth) {}

LSM9DS1::LSM9DS1(uint8_t address, uint8_t scale, uint8_t sample_rate, uint8_t bandwidth)
    : TWI::Driver(address),
      m_settings(scale, sample_rate, bandwidth),
      m_register(this) {}

bool LSM9DS1::begin() {
    //uint8_t dev_id_m = m_register.read8(LSM9DS1::DEV_ID_M);
    uint8_t dev_id_xg = m_register.read8(LSM9DS1::DEV_ID_XG);
    //trace << dev_id_m << endl;
    trace << dev_id_xg << endl;
    return /*dev_id_m == LSM9DS1_DEV_ID_M &&*/ dev_id_xg == LSM9DS1_DEV_ID_XG;
}

float LSM9DS1::read_value() {
    return 0;
}
