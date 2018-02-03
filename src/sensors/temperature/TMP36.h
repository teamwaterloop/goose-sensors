#ifndef GOOSE_SENSORS_TMP36_H
#define GOOSE_SENSORS_TMP36_H
#include <Cosa/AnalogPin.hh>

namespace wlp {

    class TMP36 {
    public:
        explicit TMP36(Board::AnalogPin analog_pin);

        double read_temperature();

    protected:

    private:
        AnalogPin pin;

    };

}

#endif //GOOSE_SENSORS_TMP36_H