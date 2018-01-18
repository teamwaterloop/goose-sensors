#include "I2CRegister.h"

using namespace wlp;

I2CRegister::I2CRegister(uint8_t i2c_addr)
        : m_driver(i2c_addr) {}

void I2CRegister::write8(uint8_t reg_addr, uint8_t data) {
    write_bytes<uint8_t>(reg_addr, data);
}

void I2CRegister::write16(uint8_t reg_addr, uint16_t data) {
    write_bytes<uint16_t>(reg_addr, data);
}

void I2CRegister::write32(uint8_t reg_addr, uint32_t data) {
    write_bytes<uint32_t>(reg_addr, data);
}

void I2CRegister::write64(uint8_t reg_addr, uint64_t data) {
    write_bytes<uint64_t>(reg_addr, data);
}

uint8_t I2CRegister::read8(uint8_t reg_addr) {
    return read_bytes<uint8_t>(reg_addr);
}

uint16_t I2CRegister::read16(uint8_t reg_addr) {
    return read_bytes<uint16_t>(reg_addr);
}

uint32_t I2CRegister::read32(uint8_t reg_addr) {
    return read_bytes<uint32_t>(reg_addr);
}

uint64_t I2CRegister::read64(uint8_t reg_addr) {
    return read_bytes<uint64_t>(reg_addr);
}
