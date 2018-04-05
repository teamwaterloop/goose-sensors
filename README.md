[![Build Status](https://travis-ci.org/waterloop/goose-sensors.svg?branch=master)](https://travis-ci.org/waterloop/goose-sensors)
# Goose 3 Sensors
This repository contains code and supporting code for the sensors on the Goose 3 Hyperloop Pod.

The AVR code is developed with [Cosa](https://github.com/mikaelpatel/Cosa) using Waterloop's build toolchain
[wcosa](https://github.com/teamwaterloop/wcosa). WLib is included as STL.

## Development Dependencies
Developing the sensor code requires
* `cmake`
* `avr-gcc` or Arduino SDK
* `wcosa`

See the WCosa readme for more information.

```bash
git clone --recursive https://github.com/teamwaterloop/goose-sensors.git
cd goose-sensors
wcosa update
```

It is recommended to fork the repo.
