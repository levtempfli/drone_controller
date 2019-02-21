#ifndef I2C1_H
#define I2C1_H

#include <stdint.h>
#include <Wire.h>
#include "config.h"

class i2c1_manager {
public:
	void i2cWrite(uint8_t registerAddress, uint8_t length, uint8_t address);
	void i2cRead(uint8_t registerAddress, uint8_t nbytes, uint8_t address);
	uint8_t i2cData[I2C1_MANAGER_MAXDATALENGTH];
	void i2c_init();
	bool get_error_state();
	uint16_t get_error_number();
private:
	bool error;
	uint16_t error_counter;
};

#endif // !I2C1_H
