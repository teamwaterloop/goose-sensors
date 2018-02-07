#include "TMP36.h"

using namespace wlp;

TMP36::TMP36(Board::AnalogPin analog_pin)
    : pin(analog_pin) {}

double TMP36::read_temperature() {
    double reading = pin.sample();
    double voltage = reading * SCALE;
    float temperature_celsius = (voltage - 0.5) * 100.0; //converting from 10 mv per degree with 500 mV offset to degrees
    return temperature_celsius;
}

void TMP36::begin() {
    pin.powerup();
}

void TMP36::sleep() {
    pin.powerdown();
}