#ifndef GOOSE_SENSORS_I2CREGISTER_H
#define GOOSE_SENSORS_I2CREGISTER_H

#include <Cosa/TWI.hh>

namespace wlp {

    class I2CRegister {
    public:
        explicit I2CRegister(uint8_t i2c_addr);

        uint8_t read8(uint8_t reg_addr);

        uint16_t read16(uint8_t reg_addr);

        uint32_t read32(uint8_t reg_addr);

        uint64_t read64(uint8_t reg_addr);

        void write8(uint8_t reg_addr, uint8_t data);

        void write16(uint8_t reg_addr, uint16_t data);

        void write32(uint8_t reg_addr, uint32_t data);

        void write64(uint8_t reg_addr, uint64_t data);

        /**
         * Read up to 8 bytes from a register.
         *
         * @tparam Integer integer type that contains the bytes
         * @param reg_addr the register address on the I2C device
         * @return the read data encoded in an integer
         */
        template<typename Integer>
        Integer read_bytes(uint8_t reg_addr);

        /**
         * Write up to 8 bytes to a register.
         *
         * @tparam Integer integer type that contains the bytes
         * @param reg_addr the register address on the I2C device
         * @param data     the data encoded in an integer
         */
        template<typename Integer>
        void write_bytes(uint8_t reg_addr, Integer data);

        template<uint8_t count>
        bool read_bytes(uint8_t reg_addr, uint8_t *dest);

    private:
        TWI::Driver m_driver;
    };

    template<typename Integer>
    Integer I2CRegister::read_bytes(uint8_t reg_addr) {
        constexpr auto bytes = static_cast<uint8_t>(sizeof(Integer));
        auto ret = static_cast<Integer>(0);
        twi.acquire(&m_driver);
        twi.write(&reg_addr, 1);
        twi.read(&ret, bytes);
        twi.release();
        return ret;
    }

    template<typename Integer>
    void I2CRegister::write_bytes(uint8_t reg_addr, Integer data) {
        constexpr auto bytes = static_cast<uint8_t>(sizeof(Integer));
        twi.acquire(&m_driver);
        twi.write(&reg_addr, 1);
        twi.write(&data, bytes);
        twi.release();
    }

    template<uint8_t count>
    bool I2CRegister::read_bytes(uint8_t reg_addr, uint8_t *dest) {
        twi.acquire(&m_driver);
        if (twi.write(&reg_addr, 1) < 0 || twi.read(&dest, count) < 0) {
            return false;
        }
        twi.release();
        return true;
    }

}

#endif //GOOSE_SENSORS_I2CREGISTER_H
