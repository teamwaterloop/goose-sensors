#ifndef GOOSE_SENSORS_LSM9DS1_H
#define GOOSE_SENSORS_LSM9DS1_H

namespace wlp {

    class photoelectricSensor {
        private:
            const Board::AnalogPin = input_pin;

        public:
            void begin();
            double read_distance();
    };
}
#endif

