#ifndef GOOSE_SENSORS_BYTEINVERT_H
#define GOOSE_SENSORS_BYTEINVERT_H

#include <utility/Tmp.h>


namespace wlp {

    template<typename, typename = void>
    struct __byte_invert_dispatch_tag
        : integral_constant<uint8_t, 0> {
    };

    template<typename Integer>
    struct __byte_invert_dispatch_tag<Integer, typename enable_if<is_same<uint8_t, Integer>::value>::type>
        : integral_constant<uint8_t, 1> {
    };

    template<typename Integer>
    struct __byte_invert_dispatch_tag<Integer, typename enable_if<is_same<uint16_t, Integer>::value>::type>
        : integral_constant<uint8_t, 2> {
    };

    template<typename Integer>
    struct __byte_invert_dispatch_tag<Integer, typename enable_if<is_same<uint32_t, Integer>::value>::type>
        : integral_constant<uint8_t, 4> {
    };

    template<typename Integer>
    struct __byte_invert_dispatch_tag<Integer, typename enable_if<is_same<uint64_t, Integer>::value>::type>
        : integral_constant<uint8_t, 8> {
    };

    uint8_t __byte_invert(uint8_t data, integral_constant<uint8_t, 1>) {
        return data;
    }

    uint16_t __byte_invert(uint16_t data, integral_constant<uint8_t, 2>) {
        return static_cast<uint16_t>((data >> 8) | (data << 8));
    }

    uint32_t __byte_invert(uint32_t data, integral_constant<uint8_t, 4>) {
        // Not implemented
        UNUSED(data);
        return 0;
    }

    uint64_t __byte_invert(uint64_t data, integral_constant<uint8_t, 8>) {
        // Not implemented
        UNUSED(data);
        return 0;
    }

    template<typename Integer>
    Integer byte_invert(Integer data) {
        constexpr auto tag = __byte_invert_dispatch_tag<Integer>();
        return __byte_invert(data, tag);
    }

}

#endif //GOOSE_SENSORS_BYTEINVERT_H
