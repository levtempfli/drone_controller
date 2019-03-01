#ifndef IMU_H
#define IMU_H

#include <stdint.h>
#include "I2C1_manager.h"
#include "timer_sub.h"

extern i2c1_manager _i2c1_mng;

class imu {
public:
	void init();
	void init_fast();
	void update();
	double get_pitch();
	double get_roll();
	double get_yaw();
	double get_temp();
private:
	void calc_acc();
	void calc_gyro();
	void calc_temp();
	void calc_compl();
	void read_raw_datas();
	timer_sub timer_s = timer_sub(IMU_TIMER_BEGINTIME, IMU_TIMER_ENDTIME, IMU_TIMER_BEGINBLOCK, IMU_TIMER_ENDBLOCK, IMU_TIMER_WARNINGTIME);
	int16_t gyro_raw_x, gyro_raw_y, gyro_raw_z, acc_raw_x, acc_raw_y, acc_raw_z, temp_raw;
	double gyro_offset_x, gyro_offset_y, gyro_offset_z;
	double gyro_transfer_x, gyro_transfer_y, gyro_transfer_z;
	double dt;
	double angle_x, angle_y, angle_z;
	double acc_x, acc_y, temp;
};

#endif // !IMU_H

