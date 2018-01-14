#include <Cosa/Types.h>

#include "Sensor.h"

using namespace wlp;

void Sensor::value_read(float value) {
    UNUSED(value);
}

float Sensor::read() {
    float value = read_value();
    value_read(value);
    return value;
}
