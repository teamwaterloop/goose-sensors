#include "TMP36.h"

using namespace wlp;

TMP36::TMP36(Board::AnalogPin analog_pin)
    : pin(analog_pin) {}

double TMP36::read_temperature() {
    pin.powerup();
    double reading = pin.sample();
    double voltage = reading * 5.0;
    voltage /= 1025.0;
    float temperature_celsius = (voltage - 0.5) * 100.0;
    pin.powerdown();
    return temperature_celsius;

}