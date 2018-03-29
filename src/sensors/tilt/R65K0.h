#ifndef GOOSE_SENSORS_R65K0_H
#define GOOSE_SENSORS_R65K0_H

#define SCALE 0.0048828
#define RSHUNT 250.0 // in Ohms

#include <Cosa/AnalogPin.hh>

namespace wlp {

    class R65K0 {
    public:
        explicit R65K0(Board::AnalogPin analog_pin);

        double read_tilt();

        void begin();

        void sleep();

    private:
        AnalogPin m_analog_pin;
    };

}

#endif //GOOSE_SENSORS_R65K0_H
