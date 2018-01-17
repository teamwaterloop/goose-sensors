#include <Cosa/Trace.hh>
#include <Cosa/UART.hh>

#include "sensors/kinematic/LSM9DS1.h"

wlp::LSM9DS1 lsm;


void setup() {
    uart.begin(9600);
    trace.begin(&uart);

    trace << "======== GOOSE 3 SENSORS ========" << endl;
    if (lsm.begin()) {
        trace << "Start Succeeded" << endl;
    } else {
        trace << "Start Failed" << endl;
    }
}

void loop() {
    delay(4000);
}
