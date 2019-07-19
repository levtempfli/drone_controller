#include "IMU.h"


void imu::init() {
	for (uint8_t i = 0; i < IMU_MAGN_CONFIG_N; i++) {
		_i2c_mng.i2cData[0] = IMU_MAGN_CONFIG_REGVAL[i];
		_i2c_mng.i2cWrite(IMU_MAGN_CONFIG_REGADR[i], 1, IMU_MAGN_I2C_ADDRESS);
	}

	_i2c_mng.i2cRead(IMU_MAGN_IDEN_STADR, 3, IMU_MAGN_I2C_ADDRESS);
	int32_t identification_value = _i2c_mng.i2cData[0];
	identification_value = (identification_value << 8) | _i2c_mng.i2cData[1];
	identification_value = (identification_value << 8) | _i2c_mng.i2cData[2];
	if (identification_value != IMU_MAGN_IDEN_VAL) {
		while (1) {
			delay(500);
			//TODO:DEBUG CLASS
			Serial.println(DBG_IMU_MAGN_INIT_ERROR);
		}
	}

	for (uint8_t i = 0; i < IMU_ACGY_CONFIG_N; i++) {
		_i2c1_mng.i2cData[0] = IMU_ACGY_CONFIG_REGVAL[i];
		_i2c1_mng.i2cWrite(IMU_ACGY_CONFIG_REGADR[i], 1, IMU_ACGY_I2C_ADDRESS);
	}

	_i2c1_mng.i2cRead(IMU_ACGY_WHO_AM_I, 1, IMU_ACGY_I2C_ADDRESS);
	if (_i2c1_mng.i2cData[0] != IMU_ACGY_I2C_ADDRESS) { // Read "WHO_AM_I" register
		while (1) {
			delay(500);
			//TODO:DEBUG CLASS
			Serial.println(DBG_IMU_ACGY_INIT_ERROR);
		}
	}
	delayMicroseconds(IMU_INIT_DELAY_SHORT);
	if (IMU_GYRO_INIT_OFFSETCALC == 0) {
		gyro_offset_x = IMU_GYR_OFFSET_X;
		gyro_offset_y = IMU_GYR_OFFSET_Y;
		gyro_offset_z = IMU_GYR_OFFSET_Z;
	}
	else {
		gyro_offset_x = 0;
		gyro_offset_y = 0;
		gyro_offset_z = 0;
		for (int i = 1; i <= IMU_GYRO_INIT_OFFSET_SAMPLE_N; i++) {
			read_raw_datas();
			gyro_offset_x += gyro_raw_x;
			gyro_offset_y += gyro_raw_y;
			gyro_offset_z += gyro_raw_z;
			delayMicroseconds(IMU_GYRO_INIT_OFFSET_DELAY);
		}
		gyro_offset_x /= IMU_GYRO_INIT_OFFSET_SAMPLE_N;
		gyro_offset_y /= IMU_GYRO_INIT_OFFSET_SAMPLE_N;
		gyro_offset_z /= IMU_GYRO_INIT_OFFSET_SAMPLE_N;
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
	angle_x_dam = angle_x;
	angle_y_dam = angle_y;
	calc_magn();
	angle_z = compass_heading;


	delayMicroseconds(IMU_INIT_DELAY_SHORT);
}

void imu::init_fast() {
	timer_s.set_new_timestamp(1);
}

void imu::read_raw_datas(){
	_i2c1_mng.i2cRead(IMU_ACGY_READRAW_REGVAL, 14, IMU_ACGY_I2C_ADDRESS);
	acc_raw_x = (int16_t)((_i2c1_mng.i2cData[0] << 8) | _i2c1_mng.i2cData[1]);
	acc_raw_y = (int16_t)((_i2c1_mng.i2cData[2] << 8) | _i2c1_mng.i2cData[3]);
	acc_raw_z = (int16_t)((_i2c1_mng.i2cData[4] << 8) | _i2c1_mng.i2cData[5]);
	temp_raw = (int16_t)((_i2c1_mng.i2cData[6] << 8) | _i2c1_mng.i2cData[7]);
	gyro_raw_x = (int16_t)((_i2c1_mng.i2cData[8] << 8) | _i2c1_mng.i2cData[9]);
	gyro_raw_y = (int16_t)((_i2c1_mng.i2cData[10] << 8) | _i2c1_mng.i2cData[11]);
	gyro_raw_z = (int16_t)((_i2c1_mng.i2cData[12] << 8) | _i2c1_mng.i2cData[13]);

	_i2c_mng.i2cRead(IMU_MAGN_READRAW_REGVAL, 6, IMU_MAGN_I2C_ADDRESS);
	mag_raw_y = (int16_t)((_i2c_mng.i2cData[0] << 8) | _i2c_mng.i2cData[1]);
	mag_raw_z = (int16_t)((_i2c_mng.i2cData[2] << 8) | _i2c_mng.i2cData[3]);
	mag_raw_x = (int16_t)((_i2c_mng.i2cData[4] << 8) | _i2c_mng.i2cData[5]); 

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
	calc_magn();
	yaw_fusion();

	// This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
	/*if ((roll < -90 && compAngleX > 90) || (roll > 90 && compAngleX < -90)) {		  
	  compAngleX = roll;
	  gyroXangle = roll;
	}*/

	timer_s.end();
}

void imu::calc_acc(){
	acc_raw_x -= IMU_ACC_OFFSET_X;
	acc_raw_y -= IMU_ACC_OFFSET_Y;

	acc_raw_x = -acc_raw_x;
	acc_raw_z = -acc_raw_z;
	acc_raw_y = -acc_raw_y;

	new_acc_x = atan(acc_raw_y / sqrt(acc_raw_x * acc_raw_x + acc_raw_z * acc_raw_z)) * RAD_TO_DEG;
	new_acc_y = atan(-acc_raw_x / sqrt(acc_raw_y * acc_raw_y + acc_raw_z * acc_raw_z)) * RAD_TO_DEG;

	if (!isnan(new_acc_x) && !isnan(new_acc_y)) {
		acc_x = new_acc_x;
		acc_y = new_acc_y;
	}

	/*Serial.print(acc_x); Serial.print("\t");
	Serial.print(acc_y); Serial.print("\t");
	Serial.println("");*/
}

void imu::calc_gyro(){
	gyro_raw_x -= gyro_offset_x;
	gyro_raw_y -= gyro_offset_y;
	gyro_raw_z -= gyro_offset_z;


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

	angle_x = IMU_COMPL_FILTER_ALFA * (angle_x)+IMU_COMPL_FILTER_1MALFA * acc_x;
	angle_y = IMU_COMPL_FILTER_ALFA * (angle_y)+IMU_COMPL_FILTER_1MALFA * acc_y;

	angle_x_dam = IMU_DAMPEN_ANG_ALFA * (angle_x_dam)+IMU_DAMPEN_ANG_1MALFA * angle_x;
	angle_y_dam = IMU_DAMPEN_ANG_ALFA * (angle_y_dam)+IMU_DAMPEN_ANG_1MALFA * angle_y;
}

void imu::calc_magn() {
	mag_raw_x = -mag_raw_x;

	mag_corr_x = (double)((double)mag_raw_x - (IMU_MAGN_OFFSET_X))*(IMU_MAGN_SCALE_X);
	mag_corr_y = (double)((double)mag_raw_y - (IMU_MAGN_OFFSET_Y))*(IMU_MAGN_SCALE_Y);
	mag_corr_z = (double)((double)mag_raw_z - (IMU_MAGN_OFFSET_Z))*(IMU_MAGN_SCALE_Z);

	mag_real_x = mag_corr_x * cos(get_pitch()*PI / 180) + mag_corr_y * sin(get_roll()*PI / 180)*sin(get_pitch()*PI / 180) + mag_corr_z * cos(get_roll()*PI / 180)*sin(get_pitch()*PI / 180);
	mag_real_y = mag_corr_y * cos(get_roll()*PI / 180) - mag_corr_z * sin(get_roll()*PI / 180);

	if (mag_real_x == 0 && mag_real_y < 0) compass_heading = 90;
	else if (mag_real_x == 0 && mag_real_y > 0) compass_heading = 270;
	else if (mag_real_x < 0) compass_heading = (double)180 - (double)atan((double)mag_real_y / mag_real_x) * 180 / PI;
	else if (mag_real_x > 0 && mag_real_y < 0) compass_heading = (double)-(double)atan((double)mag_real_y / mag_real_x) * 180 / PI;
	else if (mag_real_x > 0 && mag_real_y > 0) compass_heading = (double)360 - (double)atan((double)mag_real_y / mag_real_x) * 180 / PI;
}

void imu::yaw_fusion() {

	angle_z = IMU_YAW_FUSION_ALFA*angle_z + IMU_YAW_FUSION_1MALFA *(angle_z + course_deviation(angle_z, compass_heading));
	//angle_z = angle_z + course_deviation(angle_z, compass_heading) / 1200; //Joop formula

	if (angle_z < 0) angle_z = (double) 360 + angle_z;
	if (angle_z >= 360) angle_z = angle_z - (double) 360;
}

double imu::course_deviation(double course_c, double course_b) {
	double course_a = course_b - course_c;
	float base_course_mirrored, actual_course_mirrored;
	if (course_a < -180 || course_a > 180) {
		if (course_c > 180)base_course_mirrored = course_c - 180;
		else base_course_mirrored = course_c + 180;
		if (course_b > 180)actual_course_mirrored = course_b - 180;
		else actual_course_mirrored = course_b + 180;
		course_a = actual_course_mirrored - base_course_mirrored;
	}
	return course_a;
}

double imu::get_roll() {
	return angle_x_dam;
}

double imu::get_pitch() {
	return angle_y_dam;
}

double imu::get_yaw() {
	return angle_z;
}

double imu::get_temp() {
	return temp;
}