#include "IMU.h"


void imu::init() {
	// Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
	// Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
	// Set Gyro Full Scale Range to ±250deg/s
	// Set Accelerometer Full Scale Range to ±2g
	// Write to all four registers at once
	// PLL with X axis gyroscope reference and disable sleep mode
	for (uint8_t i = 0; i < IMU_CONFIG_N; i++) {
		_i2c1_mng.i2cData[0] = IMU_CONFIG_REGVAL[i];
		_i2c1_mng.i2cWrite(IMU_CONFIG_REGADR[i], 1, IMU_I2C_ADDRESS);
	}

	_i2c1_mng.i2cRead(IMU_WHO_AM_I, 1, IMU_I2C_ADDRESS);
	if (_i2c1_mng.i2cData[0] != IMU_I2C_ADDRESS) { // Read "WHO_AM_I" register
		while (1) {
			delay(500);
			//TODO:DEBUG CLASS
			Serial.println(DBG_IMU_INIT_ERROR);
		}
	}
	delay(100);
	if (IMU_INIT_OFFSETCALC == 0) {
		gyro_offset_x = IMU_DEFGOFFSET_X;
		gyro_offset_y = IMU_DEFGOFFSET_Y;
		gyro_offset_z = IMU_DEFGOFFSET_Z;
	}
	else {
		gyro_offset_x = 0;
		gyro_offset_y = 0;
		gyro_offset_z = 0;
		for (int i = 1; i <= IMU_INIT_OFFSET_SAMPLE_N; i++) {
			read_raw_datas();
			gyro_offset_x += gyro_raw_x;
			gyro_offset_y += gyro_raw_y;
			gyro_offset_z += gyro_raw_z;
		}
		gyro_offset_x /= IMU_INIT_OFFSET_SAMPLE_N;
		gyro_offset_y /= IMU_INIT_OFFSET_SAMPLE_N;
		gyro_offset_z /= IMU_INIT_OFFSET_SAMPLE_N;
		//TODO:DEBUG CLASS
		Serial.print(DBG_IMU_OFFSCAL_RESULT); Serial.print("\t");
		Serial.print(gyro_offset_x); Serial.print("\t");
		Serial.print(gyro_offset_y); Serial.print("\t");
		Serial.print(gyro_offset_z); Serial.println("\t");
	}

	read_raw_datas();
	calc_acc();
	angle_x = acc_x;
	angle_y = acc_y;


	delay(100);
}

void imu::init_fast() {
	timer_s.set_new_timestamp(1);
}

void imu::read_raw_datas(){
	_i2c1_mng.i2cRead(0x3B, 14, IMU_I2C_ADDRESS);
	acc_raw_x = (int16_t)((_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1]);
	acc_raw_y = (int16_t)((_i2c1_mng.i2cData[2] << 8) | _i2c1_mng.i2cData[3]);
	acc_raw_z = (int16_t)((_i2c1_mng.i2cData[4] << 8) | _i2c1_mng.i2cData[5]);
	temp_raw = (int16_t)((_i2c1_mng.i2cData[6] << 8) | _i2c1_mng.i2cData[7]);
	gyro_raw_x = (int16_t)((_i2c1_mng.i2cData[8] << 8) | _i2c1_mng.i2cData[9]);
	gyro_raw_y = (int16_t)((_i2c1_mng.i2cData[10] << 8) | _i2c1_mng.i2cData[11]);
	gyro_raw_z = (int16_t)((_i2c1_mng.i2cData[12] << 8) | _i2c1_mng.i2cData[13]);

}

void imu::update(){
	timer_s.begin();

	dt = timer_s.get_time_since_timestamp(1);
	dt = (double)dt / 1000000;
	timer_s.set_new_timestamp(1);

	read_raw_datas();
	
	calc_acc();
	calc_gyro();
	calc_temp();
	calc_compl();

	// This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
	/*if ((roll < -90 && compAngleX > 90) || (roll > 90 && compAngleX < -90)) {		  
	  compAngleX = roll;
	  gyroXangle = roll;
	}*/

	timer_s.end();
}

void imu::calc_acc(){
	acc_raw_y = -acc_raw_y;
	acc_raw_z = -acc_raw_z;

	acc_x = atan(acc_raw_y / sqrt(acc_raw_x * acc_raw_x + acc_raw_z * acc_raw_z)) * RAD_TO_DEG;
	acc_y = atan(-acc_raw_x / sqrt(acc_raw_y * acc_raw_y + acc_raw_z * acc_raw_z)) * RAD_TO_DEG;
}

void imu::calc_gyro(){
	gyro_raw_x -= gyro_offset_x;
	gyro_raw_y -= gyro_offset_y;
	gyro_raw_z -= gyro_offset_z;

	gyro_raw_y = -gyro_raw_y;

	gyro_transfer_x = (double)gyro_raw_x / IMU_GYRO_SENSITIVITY_SCALE * dt;
	gyro_transfer_y = (double)gyro_raw_y / IMU_GYRO_SENSITIVITY_SCALE * dt;
	gyro_transfer_z = (double)gyro_raw_z / IMU_GYRO_SENSITIVITY_SCALE * dt;

	/*if (abs(compAngleX) > 90)
		  gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
	*/
}

void imu::calc_temp() {
	temp = temp_raw / 340.0 + 36.53;
}

void imu::calc_compl() {
	angle_x += gyro_transfer_x;
	angle_y += gyro_transfer_y;
	angle_z += gyro_transfer_z;

	angle_y += angle_x * sin(gyro_transfer_z*PI / 180);
	angle_x -= angle_y * sin(gyro_transfer_z*PI / 180);

	angle_x = IMU_COMPL_FILTER_ALFA * (angle_x) + IMU_COMPL_FILTER_1MALFA * acc_x;
	angle_y = IMU_COMPL_FILTER_ALFA * (angle_y) + IMU_COMPL_FILTER_1MALFA * acc_y;
}

double imu::get_pitch() {
	return angle_y;
}

double imu::get_roll() {
	return angle_x;
}

double imu::get_yaw() {
	return angle_z;
}

double imu::get_temp() {
	return temp;
}