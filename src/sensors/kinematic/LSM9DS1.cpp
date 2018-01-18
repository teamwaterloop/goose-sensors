#include "LSM9DS1.h"

using namespace wlp;

#define SENSITIVITY_ACCELEROMETER_2  0.000061
#define SENSITIVITY_ACCELEROMETER_4  0.000122
#define SENSITIVITY_ACCELEROMETER_8  0.000244
#define SENSITIVITY_ACCELEROMETER_16 0.000732

LSM9DS1::AccelSettings::AccelSettings(uint8_t scale, uint8_t sample_rate, uint8_t bandwidth)
    : m_enabled(true),
      m_enable_x(true),
      m_enable_y(true),
      m_enable_z(true),
      m_scale(scale),
      m_sample_rate(sample_rate),
      m_bandwidth(bandwidth),
      m_high_res_enable(false),
      m_high_res_bandwidth(0) {}

LSM9DS1::LSM9DS1(
    uint8_t address_m,
    uint8_t address_ag,
    uint8_t scale,
    uint8_t sample_rate,
    uint8_t bandwidth)
    : m_accel_settings(scale, sample_rate, bandwidth),
      m_register_m(address_m),
      m_register_ag(address_ag) {}

bool LSM9DS1::begin() {
    constrain_scales();
    accel_set_res();

    uint8_t dev_id_m = m_register_m.read8(LSM9DS1::DEV_ID_M);
    uint8_t dev_id_xg = m_register_ag.read8(LSM9DS1::DEV_ID_XG);
    if (dev_id_m != LSM9DS1_DEV_ID_M || dev_id_xg != LSM9DS1_DEV_ID_XG) {
        return false;
    }

    accel_init();
    return true;
}

void LSM9DS1::constrain_scales() {
    if (m_accel_settings.m_scale != AccelScale::A_SCALE_2G &&
        m_accel_settings.m_scale != AccelScale::A_SCALE_4G &&
        m_accel_settings.m_scale != AccelScale::A_SCALE_8G &&
        m_accel_settings.m_scale != AccelScale::A_SCALE_16G) {
        m_accel_settings.m_scale = AccelScale::A_SCALE_2G;
    }
}

void LSM9DS1::accel_set_res() {
    switch (m_accel_settings.m_scale) {
        case AccelScale::A_SCALE_2G:
            m_accel_res = SENSITIVITY_ACCELEROMETER_2;
            break;
        case AccelScale::A_SCALE_4G:
            m_accel_res = SENSITIVITY_ACCELEROMETER_4;
            break;
        case AccelScale::A_SCALE_8G:
            m_accel_res = SENSITIVITY_ACCELEROMETER_8;
            break;
        case AccelScale::A_SCALE_16G:
            m_accel_res = SENSITIVITY_ACCELEROMETER_16;
            break;
        default:
            break;
    }
}

void LSM9DS1::accel_init() {
    uint8_t t_reg_value = 0x0;

    t_reg_value |=
        (m_accel_settings.m_enable_x << 3) ||
        (m_accel_settings.m_enable_y << 4) ||
        (m_accel_settings.m_enable_z << 5);
    m_register_ag.write8(CTRL_REG5_XL, t_reg_value);

    t_reg_value = 0;
    if (m_accel_settings.m_enabled) {
        t_reg_value |= (m_accel_settings.m_sample_rate & 0x07) << 5;
    }
    switch (m_accel_settings.m_scale) {
        case AccelScale::A_SCALE_4G:
            t_reg_value |= 0x2 << 3;
            break;
        case AccelScale::A_SCALE_8G:
            t_reg_value |= 0x3 << 3;
            break;
        case AccelScale::A_SCALE_16G:
            t_reg_value |= 0x1 << 3;
            break;
        default:
            t_reg_value |= 0x0 << 3;
            break;
    }
    if (m_accel_settings.m_bandwidth < ABW::A_ABW_AUTO) {
        t_reg_value |= 1 << 2;
        t_reg_value |= m_accel_settings.m_bandwidth & 0x03;
    }
    m_register_ag.write8(CTRL_REG6_XL, t_reg_value);

    t_reg_value = 0;
    if (m_accel_settings.m_high_res_enable) {
        t_reg_value |= 1 << 7;
        t_reg_value |= (m_accel_settings.m_high_res_bandwidth & 0x03) << 5;
    }
    m_register_ag.write8(CTRL_REG7_XL, t_reg_value);
}


