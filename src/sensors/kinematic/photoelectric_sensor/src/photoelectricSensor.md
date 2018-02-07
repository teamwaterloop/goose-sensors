## Balluff 6K-RA02-S75 Photoelectric Sensor Wiring

#### Materials

* 24V power supply
* Two 12 kOhm resistors
* Backbone Cable (with 4 wires)
* Jumper Wire

#### Reference for Sensor Setup

[Here are the pins on the sensor.](https://imgur.com/0UM2vjM)

The labelled pins correspond to the following colored wires in the picture of the circuit (linked below)

1. Brown Cable
1. Blue
1. Black
1. White


#### Steps for Circuit Assembly

[View this picture of the circuit for guidance.](https://imgur.com/Hhm4pCC)

1. __Power:__ Connect brown cable to positive terminal of power supply
1. __Ground:__ Connect black and blue cable to negative terminal of power supply
1. __Data Cable:__ Connect white cable to two 12kOhm resistors in series
1. __Jumper to Arduino:__ Connect green jumper cable in series with resistors to Arduino analog pin

