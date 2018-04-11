#include <Cosa/Trace.hh>
#include <Cosa/UART.hh>

void setup() {
    uart.begin(9600);
    trace.begin(&uart);
    trace << "======== GOOSE 3 SENSORS ========" << endl;
}

void loop() {
    delay(1000);
}
