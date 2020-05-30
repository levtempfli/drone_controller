#include "I2C1_manager.h"

void i2c1_manager::i2cWrite(uint8_t registerAddress, uint8_t length, uint8_t address) {
	if (length > I2C1_MANAGER_MAXDATALENGTH) {
		error = 1;
		error_counter++;
	}
	Wire1.beginTransmission(address);
	Wire1.write(registerAddress);
	Wire1.write(i2cData, length);
	uint8_t rcode = Wire1.endTransmission(I2C1_MANAGER_RELEASEBUS);
	if (rcode) {
		error = 1;
		error_counter++;
	}
	return;
}

void i2c1_manager::i2cRead(uint8_t registerAddress, uint8_t nbytes, uint8_t address) {
	if (nbytes > I2C1_MANAGER_MAXDATALENGTH) {
		error = 1;
		error_counter++;
	}
	Wire1.beginTransmission(address);
	Wire1.write(registerAddress);
	uint8_t rcode = Wire1.endTransmission(I2C1_MANAGER_RELEASEBUS);
	if (rcode) {
		error = 1;
		error_counter++;
		return;
	}
	Wire1.requestFrom(address, nbytes, (uint8_t)I2C1_MANAGER_RELEASEBUS);
	for (uint8_t i = 0; i < nbytes; i++) {
		if (Wire1.available())
			i2cData[i] = Wire1.read();
		else {
			error = 1;
			error_counter++;
		}
	}
	return;
}

void i2c1_manager::i2c_init() {
	Wire1.begin();
	Wire1.setClock(I2C1_MANAGER_CLOCK);
	error = 0;
	error_counter = 0;
}

bool i2c1_manager::get_error_state() {
	return error;
}

uint16_t i2c1_manager::get_error_number() {
	return error_counter;
}
