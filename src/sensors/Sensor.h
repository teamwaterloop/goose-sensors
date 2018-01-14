#ifndef GOOSE_SENSORS_SENSOR_H
#define GOOSE_SENSORS_SENSOR_H

namespace wlp {

    class Sensor {
    protected:
        virtual float read_value() = 0;

        virtual void value_read(float value);

    public:
        float read();
    };

}

#endif //GOOSE_SENSORS_SENSOR_H
