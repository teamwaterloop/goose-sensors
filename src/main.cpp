#include <Cosa/Trace.hh>
#include <Cosa/UART.hh>

#include "sensors/temperature/TMP006.h"

wlp::TMP006 tmp;

void setup() {
    uart.begin(9600);
    trace.begin(&uart);

    trace << "======== GOOSE 3 SENSORS ========" << endl;
    if (tmp.begin()) {
        trace << "TMP006 Start Succeeded" << endl;
    } else {
        trace << "TMP006 Start Failed" << endl;
        while (true) {
            delay(50);
        }
    }
}

void loop() {
    trace << "Die Temp: " << tmp.read_die_temperature() << endl;
    trace << "Obj Temp: " << tmp.read_obj_temperature() << endl;
    trace << endl;
    delay(4000);
}
