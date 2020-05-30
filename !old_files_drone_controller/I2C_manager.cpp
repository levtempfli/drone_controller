#include "I2C_manager.h"

void i2c_manager::i2cWrite(uint8_t registerAddress, uint8_t length, uint8_t address) {
	if (length > I2C_MANAGER_MAXDATALENGTH) {
		error = 1;
		error_counter++;
	}
	Wire.beginTransmission(address);
	Wire.write(registerAddress);
	Wire.write(i2cData, length);
	uint8_t rcode = Wire.endTransmission(I2C_MANAGER_RELEASEBUS);
	if (rcode) {
		error = 1;
		error_counter++;
	}
	return;
}

void i2c_manager::i2cRead(uint8_t registerAddress, uint8_t nbytes, uint8_t address) {
	if (nbytes > I2C_MANAGER_MAXDATALENGTH) {
		error = 1;
		error_counter++;
	}
	Wire.beginTransmission(address);
	Wire.write(registerAddress);
	uint8_t rcode = Wire.endTransmission(I2C_MANAGER_RELEASEBUS);
	if (rcode) {
		error = 1;
		error_counter++;
		return;
	}
	Wire.requestFrom(address, nbytes, (uint8_t)I2C_MANAGER_RELEASEBUS);
	for (uint8_t i = 0; i < nbytes; i++) {
		if (Wire.available())
			i2cData[i] = Wire.read();
		else {
			error = 1;
			error_counter++;
		}
	}
	return;
}

void i2c_manager::i2c_init(){
	Wire.begin();
	Wire.setClock(I2C_MANAGER_CLOCK);
	error = 0;
	error_counter = 0;
}

bool i2c_manager::get_error_state(){
	return error;
}

uint16_t i2c_manager::get_error_number(){
	return error_counter;
}
