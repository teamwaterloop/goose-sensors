#include "TMP36.h"

using namespace wlp;

TMP36::TMP36(Board::AnalogPin analog_pin)
    : m_analog_pin(analog_pin) {}

double TMP36::read_temperature() {
    uint16_t reading = m_analog_pin.sample();
    double voltage = static_cast<double>(reading) * SCALE;
    // Converting from 10 mV per degree Celsius with 500 mV offset to degrees
    double temperature_celsius = (voltage - 0.5) * 100.0;
    return temperature_celsius;
}

void TMP36::begin() {
    m_analog_pin.powerup();
}

void TMP36::sleep() {
    m_analog_pin.powerdown();
}
