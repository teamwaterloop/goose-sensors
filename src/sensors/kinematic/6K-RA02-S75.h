#ifndef GOOSE_SENSORS_LSM9DS1_H
#define GOOSE_SENSORS_LSM9DS1_H

#include <Cosa/Board.hh>
#include <Cosa/AnalogPin.hh>

namespace wlp {

    class PhotoelectricSensor {
        private:
            AnalogPin m_input_pin;

        public:
            PhotoelectricSensor(Board::AnalogPin input_pin);
            void begin();
            void sleep();
            double read_distance();
    };
}
#endif

