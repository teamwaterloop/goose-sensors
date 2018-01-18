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
    if (lsm.accel_available()) {
        trace << "Accel ready" << endl;
        lsm.accel_read();
    } else {
        trace << "Accel not ready" << endl;
    }
    trace << lsm.accel_x() << ", " << lsm.accel_y() << ", " << lsm.accel_z() << endl;
    delay(1000);
}
