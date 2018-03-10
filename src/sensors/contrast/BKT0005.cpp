#include "BKT0005.h"

using namespace wlp;

BKT0005::BKT0005(Board::AnalogPin analog_pin, Board::DigitalPin pnp_pin)
    : m_analog_pin(analog_pin), m_pnp_pin(pnp_pin) {}

uint16_t BKT0005::read_contrast() {
    return m_analog_pin.sample();
}

bool BKT0005::read_pnp() {
	return m_pnp_pin.is_on();
}

void BKT0005::begin() {
    m_analog_pin.powerup();
}

void BKT0005::sleep() {
    m_analog_pin.powerdown();
}
