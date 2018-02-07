#include "Cosa/Watchdog.hh"
#include "Cosa/Memory.h"
#include "Cosa/Trace.hh"
#include "Cosa/UART.hh"
#include "Cosa/EEPROM.hh"
#include "Cosa/AnalogPin.hh"
#include "6K-RA02-S75.h"

using namespace wlp;

photoelectricSensor::photoelectricSensor(const Board::AnalogPin in){
    Board::AnalogPin pin = in;
}

void photoelectricSensor::begin(){
      AnalogPin sensor(in);
      AnalogPin::powerup();
}
double photoelectricSensor::read_distance(){
  return sensor.sample()/10.0;
}

photoelectricSensor pe_sensor(Board::A0);

void setup()
{
  // Serial output
  uart.begin(9600);
  trace.begin(&uart, PSTR("CosaEEPROM: started"));
  TRACE(free_memory());
  Watchdog::begin();
  pe_sensor.begin();
}

void loop()
{
  trace << pe_sensor.read_distance() << endl;
}
