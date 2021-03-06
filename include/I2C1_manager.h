#ifndef I2C1_H
#define I2C1_H

#include "config.h"
#include <Wire.h>
#include <stdint.h>

// I2C1 manager class
class i2c1_manager
{
  public:
    i2c1_manager(){};
    i2c1_manager(const i2c1_manager &) = delete;
    void i2cWrite(uint8_t registerAddress, uint8_t length, uint8_t address); // write
    void i2cRead(uint8_t registerAddress, uint8_t nbytes, uint8_t address);  // read
    uint8_t i2cData[CFG::I2C1_man::max_data_length]; // this will be written or here will be read the data
    void i2c_init();                                 // init
    bool get_error_state();                          // error state
    uint16_t get_error_number();                     // error number
  private:
    bool error;
    uint16_t error_counter;
};

#endif // !I2C1_H
