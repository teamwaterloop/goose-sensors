#include "sensors/temperature/TMP006.h"

wlp::TMP006 tmp;

void setup() {
    if (tmp.begin()) {
        trace << "Start succeeded" << endl;
    } else {
        trace << "Start failed" << endl;
    }
}

void loop() {
    trace << "Die Temp: " << tmp.read_die_temperature() << endl;
    trace << "Obj Temp: " << tmp.read_obj_temperature() << endl;
    trace << endl;
    delay(4000);
}
