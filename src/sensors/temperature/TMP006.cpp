#include <math.h>

#include "TMP006.h"
#include "../../register/ByteInvert.h"

using namespace wlp;

TMP006::TMP006(uint8_t address, uint16_t sample_rate)
    : m_sample_rate(sample_rate),
      m_register(address) {}

bool TMP006::begin() {
    m_register.write16(TMP006::CONFIG, TMP006::CFG_MODEON | TMP006::CFG_DRDYEN | m_sample_rate);
    auto man_id = byte_invert<uint16_t>(m_register.read16(TMP006::MAN_ID));
    auto dev_id = byte_invert<uint16_t>(m_register.read16(TMP006::DEV_ID));
    return man_id == TMP006_MAN_ID && dev_id == TMP006_DEV_ID;
}

void TMP006::sleep() {
    uint16_t config = m_register.read16(TMP006::CONFIG);
    config &= ~TMP006::CFG_MODEON;
    m_register.write16(TMP006::CONFIG, config);
}

void TMP006::wake() {
    uint16_t config = m_register.read16(TMP006::CONFIG);
    config |= TMP006::CFG_MODEON;
    m_register.write16(TMP006::CONFIG, config);
}

int16_t TMP006::read_raw_die_temperature() {
    auto raw_value = static_cast<int16_t>(byte_invert<uint16_t>(m_register.read16(TMP006::TAMB)));
    raw_value >>= 2;
    return raw_value;
}

int16_t TMP006::read_raw_voltage() {
    return static_cast<int16_t>(byte_invert<uint16_t>(m_register.read16(TMP006::VOBJ)));
}

double TMP006::read_die_temperature() {
    return read_raw_die_temperature() * 0.03125;
}

double TMP006::read_obj_temperature() {
    double die_temp = read_die_temperature() + 273.15;
    double vobj = read_raw_voltage() * 1.5625e-7;
    double die_ref_temp = die_temp - TMP006_TREF;
    double die_ref_temp_sq = die_ref_temp * die_ref_temp;
    double S =
        1 +
        TMP006_A1 * die_ref_temp +
        TMP006_A2 * die_ref_temp_sq;
    S *= TMP006_S0 * 1e-14;
    double vos =
        TMP006_B0 +
        TMP006_B1 * die_ref_temp +
        TMP006_B2 * die_ref_temp_sq;
    double vdiff = vobj - vos;
    double f_vobj = vdiff + TMP006_C2 * vdiff * vdiff;
    double die_temp_sq = die_temp * die_temp;
    double temperature = sqrt(sqrt(die_temp_sq * die_temp_sq + f_vobj / S));
    return temperature - 273.15;
}
