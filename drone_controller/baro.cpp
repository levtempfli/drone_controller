#include "baro.h"

void baro::init() {
	oversampling = BARO_MODE;
	sealevelpressure = BARO_DEF_SEALEVELPRESSURE;

	_i2c1_mng.i2cRead(BARO_CHIPID_REG, 1, BARO_I2C_ADDR);

	if (_i2c1_mng.i2cData[0] != BARO_CHIPID_VAL) {
		dout.fatal_error(DBG_BARO_INIT_ERROR);
	}

	_i2c1_mng.i2cRead(BARO_CAL_AC1, 2, BARO_I2C_ADDR);
	ac1 = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];
	_i2c1_mng.i2cRead(BARO_CAL_AC2, 2, BARO_I2C_ADDR);
	ac2 = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];
	_i2c1_mng.i2cRead(BARO_CAL_AC3, 2, BARO_I2C_ADDR);
	ac3 = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];
	_i2c1_mng.i2cRead(BARO_CAL_AC4, 2, BARO_I2C_ADDR);
	ac4 = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];
	_i2c1_mng.i2cRead(BARO_CAL_AC5, 2, BARO_I2C_ADDR);
	ac5 = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];
	_i2c1_mng.i2cRead(BARO_CAL_AC6, 2, BARO_I2C_ADDR);
	ac6 = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];
	_i2c1_mng.i2cRead(BARO_CAL_B1, 2, BARO_I2C_ADDR);
	b1 = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];
	_i2c1_mng.i2cRead(BARO_CAL_B2, 2, BARO_I2C_ADDR);
	b2 = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];
	_i2c1_mng.i2cRead(BARO_CAL_MB, 2, BARO_I2C_ADDR);
	mb = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];
	_i2c1_mng.i2cRead(BARO_CAL_MC, 2, BARO_I2C_ADDR);
	mc = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];
	_i2c1_mng.i2cRead(BARO_CAL_MD, 2, BARO_I2C_ADDR);
	md = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];

	rot_sum = 0;
	for (int i = 0; i < BARO_NUM_OF_AVG; i++) {
		start_temp();
		delayMicroseconds(BARO_TEMP_MEAS_DURATION);
		read_temp();

		start_press();
		delayMicroseconds(BARO_PRES_MEAS_DURATION);
		read_press();

		rot_mem[i] = pressure;
		rot_sum += pressure;
	}
	
	rot_mem_i = 1;
	rot_avg = rot_sum / BARO_NUM_OF_AVG;

	compl_2 = rot_avg;
	compl_1_corr = rot_avg;

	calc_altitude();

	start_temp();
	timer_s.set_new_timestamp(0);
	curr_measurement = 0;
	

}

void baro::start_temp() {
	_i2c1_mng.i2cData[0] = BARO_CMD_READTEMP;
	_i2c1_mng.i2cWrite(BARO_CMD_CONTROL, 1, BARO_I2C_ADDR);
}

void baro::start_press() {
	_i2c1_mng.i2cData[0] = BARO_CMD_READPRESS + (oversampling << 6);
	_i2c1_mng.i2cWrite(BARO_CMD_CONTROL, 1, BARO_I2C_ADDR);
}

void baro::read_temp() {
	_i2c1_mng.i2cRead(BARO_DATA, 2, BARO_I2C_ADDR);
	UT = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];
	int32_t Y1 = (UT - (int32_t)ac6) * ((int32_t)ac5) >> 15;
	int32_t Y2 = ((int32_t)mc << 11) / (Y1 + (int32_t)md);
	B5 = Y1 + Y2;
	temp = (B5 + 8) >> 4;
	temp /= 10;
	
}

void baro::read_press() {
	uint32_t raw;
	int32_t UP, B3, B6, X1, X2, X3;
	uint32_t B4, B7;

	_i2c1_mng.i2cRead(BARO_DATA, 3, BARO_I2C_ADDR);
	raw = (_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1];

	raw <<= 8;
	raw |= _i2c1_mng.i2cData[2];
	raw >>= (8 - oversampling);

	UP = raw;

	B6 = B5 - 4000;
	X1 = ((int32_t)b2 * ((B6 * B6) >> 12)) >> 11;
	X2 = ((int32_t)ac2 * B6) >> 11;
	X3 = X1 + X2;
	B3 = ((((int32_t)ac1 * 4 + X3) << oversampling) + 2) / 4;

	X1 = ((int32_t)ac3 * B6) >> 13;
	X2 = ((int32_t)b1 * ((B6 * B6) >> 12)) >> 16;
	X3 = ((X1 + X2) + 2) >> 2;
	B4 = ((uint32_t)ac4 * (uint32_t)(X3 + 32768)) >> 15;
	B7 = ((uint32_t)UP - B3) * (uint32_t)(50000UL >> oversampling);

	if (B7 < 0x80000000) {
		pressure = (B7 * 2) / B4;
	}
	else {
		pressure = (B7 / B4) * 2;
	}
	X1 = (pressure >> 8) * (pressure >> 8);
	X1 = (X1 * 3038) >> 16;
	X2 = (-7357 * pressure) >> 16;

	pressure = pressure + ((X1 + X2 + (int32_t)3791) >> 4);
}

void baro::calc_altitude(){
	altitude = (double)BARO_ALT_CALC_CONST1 * (1.0 - pow(compl_1_corr / (double)sealevelpressure, BARO_ALT_CALC_CONST2));
}

void baro::set_altitude(double new_altitude){
	sealevelpressure = (int32_t)(compl_1_corr / pow(1.0 - new_altitude / BARO_ALT_CALC_CONST1, (1/ BARO_ALT_CALC_CONST2)));
	calc_altitude();
}

void baro::update(){
	timer_s.begin();

	if (new_pressure_data == 1) new_pressure_data = 0;

	if (curr_measurement == 0) {
		//delayMicroseconds(BARO_TEMP_MEAS_DURATION);
		if (timer_s.get_time_since_timestamp(0) >= BARO_TEMP_MEAS_DURATION) {
			read_temp();
			start_press();
			timer_s.set_new_timestamp(1);
			curr_measurement = 1;
		}
	}
	if (curr_measurement == 1) {
		//delayMicroseconds(BARO_PRES_MEAS_DURATION);
		if (timer_s.get_time_since_timestamp(1) >= BARO_PRES_MEAS_DURATION) {
			read_press();
			new_pressure_data = 1;
			start_temp();
			timer_s.set_new_timestamp(0);
			curr_measurement = 0;
		}
		
	}

	if (new_pressure_data) {
		rot_sum = rot_sum - rot_mem[rot_mem_i];
		rot_mem[rot_mem_i] = pressure;
		rot_sum = rot_sum + rot_mem[rot_mem_i];
		rot_mem_i++;
		if (rot_mem_i == BARO_NUM_OF_AVG - 1) rot_mem_i = 0;
		rot_avg = (double)rot_sum / BARO_NUM_OF_AVG;

		compl_2 = BARO_COMPL_FILTER_ALFA *compl_2 + BARO_COMPL_FILTER_1MALFA *rot_avg;
		compl_1_corr = BARO_COMPL_FILTER_ALFA *compl_1_corr + BARO_COMPL_FILTER_1MALFA *rot_avg;

		double actual_pressure_diff = compl_1_corr - rot_avg;
		if (actual_pressure_diff > BARO_CORR_MAX_DIFF) actual_pressure_diff = BARO_CORR_MAX_DIFF;                                                    //If the difference is larger then 8 limit the difference to 8.
		if (actual_pressure_diff < -BARO_CORR_MAX_DIFF) actual_pressure_diff = -BARO_CORR_MAX_DIFF;                                                  //If the difference is smaller then -8 limit the difference to -8.
		if (actual_pressure_diff > BARO_CORR_MIN_DIFF || actual_pressure_diff < -BARO_CORR_MIN_DIFF) compl_1_corr -= actual_pressure_diff / BARO_CORR_ADJ_DIV; //If the difference is larger then 1 or smaller then -1 the slow average is adjuste based on the error between the fast and slow average.

		calc_altitude();
	}
	
	timer_s.end();
}

double baro::get_pressure(uint8_t mode){//1(default)-Corrected data(average & complementary fusion), 2-average data, 3-complementary data, 4-raw data
	switch (mode){
	case 1:
		return compl_1_corr;
		break;
	case 2:
		return rot_avg;
		break;
	case 3:
		return compl_2;
		break;
	case 4:
		return pressure;
		break;
	default:
		return compl_1_corr;
		break;
	}
}

double baro::get_temperature(){
	return temp;
}

double baro::get_altitude(){
	return altitude;
}

bool baro::is_there_new_pressure(){
	return new_pressure_data;
}

