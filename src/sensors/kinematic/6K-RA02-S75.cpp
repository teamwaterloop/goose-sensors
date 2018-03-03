#include "6K-RA02-S75.h"

using namespace wlp;

PhotoelectricSensor::PhotoelectricSensor(const Board::AnalogPin in) :
    //constructs sensor class with the specified analog pin
    m_input_pin(in) {}

void PhotoelectricSensor::begin() {
    //activates sensor
    m_input_pin.powerup();
}

void PhotoelectricSensor::sleep() {
    // deactivates sensor
    m_input_pin.powerdown();
}

double PhotoelectricSensor::read_distance() {
    // returns the distance measured in centimeters
    return m_input_pin.sample() / 10.0;
}