#ifndef GOOSE_SENSORS_BKT0005_H
#define GOOSE_SENSORS_BKT0005_H

#include <Cosa/AnalogPin.hh>
#include <Cosa/InputPin.hh>

namespace wlp {

    class BKT0005 {
    public:
        BKT0005(Board::AnalogPin analog_pin, Board::DigitalPin pnp_pin);

        uint16_t read_contrast();

	bool read_pnp();

        void begin();

        void sleep();

    private:
        AnalogPin m_analog_pin;
	InputPin m_pnp_pin;
    };

}

#endif //GOOSE_SENSORS_BKT0005_H
