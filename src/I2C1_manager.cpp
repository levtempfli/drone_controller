#include "I2C1_manager.h"

//Write to slave address a number of bytes starting with a the register adress
void i2c1_manager::i2cWrite(uint8_t registerAddress, uint8_t length, uint8_t address) {
	if (length > CFG::I2C1_man::max_data_length) {
		error = 1;
		error_counter++;
	}
	Wire1.beginTransmission(address);
	Wire1.write(registerAddress);
	Wire1.write(i2cData, length);
	uint8_t rcode = Wire1.endTransmission(CFG::I2C1_man::release_bus);
	if (rcode) {
		error = 1;
		error_counter++;
	}
	return;
}

//Read to slave address a number of bytes starting with a the register adress
void i2c1_manager::i2cRead(uint8_t registerAddress, uint8_t nbytes, uint8_t address) {
	if (nbytes > CFG::I2C1_man::max_data_length) {
		error = 1;
		error_counter++;
	}
	Wire1.beginTransmission(address);
	Wire1.write(registerAddress);
	uint8_t rcode = Wire1.endTransmission(CFG::I2C1_man::release_bus);
	if (rcode) {
		error = 1;
		error_counter++;
		return;
	}
	Wire1.requestFrom(address, nbytes, (uint8_t)CFG::I2C1_man::release_bus);
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

//Init
void i2c1_manager::i2c_init() {
	Wire1.begin();
	Wire1.setClock(CFG::I2C1_man::clock_speed);
	error = 0;
	error_counter = 0;
}

//error  state
bool i2c1_manager::get_error_state() {
	return error;
}

//error number
uint16_t i2c1_manager::get_error_number() {
	return error_counter;
}
