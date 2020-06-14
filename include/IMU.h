#ifndef IMU_H
#define IMU_H

#include "I2C1_manager.h"
#include "I2C_manager.h"
#include "debug_in.h"
#include "debug_out.h"
#include "timer_sub.h"
#include <stdint.h>

class imu_control
{
  public:
    imu_control(timer_main &tm, i2c_manager &i2cm, i2c1_manager &i2c1m, debug_out &dou); // Constructor
    imu_control() = delete;
    imu_control(const imu_control &) = delete;
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
    void calc_compl();
    void read_raw_datas();
    timer_sub timer_s;
    timer_main &timer_m;
    i2c_manager &i2c_mng;
    i2c1_manager &i2c1_mng;
    debug_out &dout;
    int16_t gyro_raw_x, gyro_raw_y, gyro_raw_z, acc_raw_x, acc_raw_y, acc_raw_z, temp_raw;
    double new_acc_x, new_acc_y;
    double gyro_offset_x, gyro_offset_y, gyro_offset_z;
    double gyro_transfer_x, gyro_transfer_y, gyro_transfer_z;
    double dt;
    double angle_x, angle_y, angle_z;
    double angle_x_dam, angle_y_dam;
    double acc_x, acc_y, temp;
    int16_t mag_raw_x, mag_raw_y, mag_raw_z;
    double mag_corr_x, mag_corr_y, mag_corr_z, mag_real_x, mag_real_y;
    double compass_heading;
    void calc_magn();
    void yaw_fusion();
    double course_deviation(double course_c, double course_b);
};

#endif // !IMU_H
