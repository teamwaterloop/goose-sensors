#ifndef GOOSE_SENSORS_VOLTAGEINTERFACE_H
#define GOOSE_SENSORS_VOLTAGEINTERFACE_H

#include <utility/Tmp.h>
#include <Cosa/AnalogPin.hh>

namespace wlp {

    template<
        typename Number,
        Board::AnalogPin t_analog_pin = Board::AnalogPin::A0,
        Board::Reference t_reference = Board::AVCC_REFERENCE,
        typename = typename enable_if<is_arithmetic<Number>::value>::type
    >
    class VoltageInterface {
    public:
        VoltageInterface(Number min, Number max)
            : m_analog_pin(t_analog_pin, t_reference),
              m_min(min),
              m_range(max - min) {}

        const AnalogPin *analog_pin() const {
            return &m_analog_pin;
        }

        Number read_value() {
            constexpr auto descale = static_cast<Number>(t_reference);
            auto raw_value = static_cast<Number>(m_analog_pin.sample());
            return raw_value / descale * m_range + m_min;
        }

    private:
        AnalogPin m_analog_pin;
        Number m_min;
        Number m_range;
    };

}

#endif //GOOSE_SENSORS_VOLTAGEINTERFACE_H
