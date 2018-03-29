#include "R65K0.h"

using namespace wlp;

/* 0 degrees at current Ic = 4mA + (20mA - 4mA)/2, voltage Vc = Ic * Rshunt */
#define CENTER_OFFSET (0.012 * RSHUNT)
/* 360 degrees over entire range, which is (20mA - 4mA) * Rshunt */
#define DEGREES_PER_VOLT 360.0 / (0.016 * RSHUNT)

R65K0::R65K0(Board::AnalogPin analog_pin)
    : m_analog_pin(analog_pin) {}

double R65K0::read_tilt() {
    uint16_t reading = m_analog_pin.sample();
    double voltage = static_cast<double>(reading) * SCALE;
    double tilt = (voltage - CENTER_OFFSET) * DEGREES_PER_VOLT;
    return tilt;
}

void R65K0::begin() {
    m_analog_pin.powerup();
}

void R65K0::sleep() {
    m_analog_pin.powerdown();
}
