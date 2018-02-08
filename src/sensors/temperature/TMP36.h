#ifndef GOOSE_SENSORS_TMP36_H
#define GOOSE_SENSORS_TMP36_H

#define SCALE 0.0048828

#include <Cosa/AnalogPin.hh>

namespace wlp {

    class TMP36 {
    public:
        explicit TMP36(Board::AnalogPin analog_pin);

        double read_temperature();

        void begin();

        void sleep();

    private:
        AnalogPin m_analog_pin;
    };

}

#endif //GOOSE_SENSORS_TMP36_H
