#include "I2C_manager.h"

// Write to slave address a number of bytes starting with a the register adress
void i2c_manager::i2cWrite(uint8_t registerAddress, uint8_t length, uint8_t address)
{
    if (length > CFG::I2C_man::max_data_length)
    {
        error = 1;
        error_counter++;
    }
    Wire.beginTransmission(address);
    Wire.write(registerAddress);
    Wire.write(i2cData, length);
    uint8_t rcode = Wire.endTransmission(CFG::I2C_man::release_bus);
    if (rcode)
    {
        error = 1;
        error_counter++;
    }
    return;
}

// Read to slave address a number of bytes starting with a the register adress
void i2c_manager::i2cRead(uint8_t registerAddress, uint8_t nbytes, uint8_t address)
{
    if (nbytes > CFG::I2C_man::max_data_length)
    {
        error = 1;
        error_counter++;
    }
    Wire.beginTransmission(address);
    Wire.write(registerAddress);
    uint8_t rcode = Wire.endTransmission(CFG::I2C_man::release_bus);
    if (rcode)
    {
        error = 1;
        error_counter++;
        return;
    }
    Wire.requestFrom(address, nbytes, (uint8_t)CFG::I2C_man::release_bus);
    for (uint8_t i = 0; i < nbytes; i++)
    {
        if (Wire.available())
            i2cData[i] = Wire.read();
        else
        {
            error = 1;
            error_counter++;
        }
    }
    return;
}

// Initialization
void i2c_manager::i2c_init()
{
    Wire.begin();
    Wire.setClock(CFG::I2C_man::clock_speed);
    error = 0;
    error_counter = 0;
}

// error state
bool i2c_manager::get_error_state()
{
    return error;
}

// error number
uint16_t i2c_manager::get_error_number()
{
    return error_counter;
}
