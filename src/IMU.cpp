#include "IMU.h"

imu_control::imu_control(timer_main &tm, i2c_manager &i2cm, i2c1_manager &i2c1m, debug_out &dou)
    : timer_s(CFG::IMU::timer::begin_time, CFG::IMU::timer::end_time, CFG::IMU::timer::begin_block,
              CFG::IMU::timer::end_block, CFG::IMU::timer::warning_time, tm),
      timer_m(tm), i2c_mng(i2cm), i2c1_mng(i2c1m), dout(dou)
{
}

void imu_control::init()
{
    for (uint8_t i = 0; i < CFG::IMU::magneto::settings_n; i++)
    {
        i2c_mng.i2cData[0] = CFG::IMU::magneto::settings_reg_val[i];
        i2c_mng.i2cWrite(CFG::IMU::magneto::settings_reg_addr[i], 1, CFG::IMU::magneto::I2C_address);
    }

    i2c_mng.i2cRead(CFG::IMU::magneto::ident_start_addr, 3, CFG::IMU::magneto::I2C_address);
    int32_t identification_value = i2c_mng.i2cData[0];
    identification_value = (identification_value << 8) | i2c_mng.i2cData[1];
    identification_value = (identification_value << 8) | i2c_mng.i2cData[2];
    if (identification_value != CFG::IMU::magneto::ident_val)
    {
        dout.fatal_error(CFG::IMU::msg::magn_init_error);
    }

    for (uint8_t i = 0; i < CFG::IMU::accgyro::settings_n; i++)
    {
        i2c1_mng.i2cData[0] = CFG::IMU::accgyro::settings_reg_val[i];
        i2c1_mng.i2cWrite(CFG::IMU::accgyro::settings_reg_addr[i], 1, CFG::IMU::accgyro::I2C_address);
    }

    i2c1_mng.i2cRead(CFG::IMU::accgyro::who_am_i_reg, 1, CFG::IMU::accgyro::I2C_address);
    if (i2c1_mng.i2cData[0] != CFG::IMU::accgyro::I2C_address)
    { // Read "WHO_AM_I" register
        dout.fatal_error(CFG::IMU::msg::acgy_init_error);
    }
    delayMicroseconds(CFG::IMU::init_delays);
    if (CFG::IMU::accgyro::gyro::offset_calc == 0)
    {
        gyro_offset_x = CFG::IMU::accgyro::gyro::def_offset_x;
        gyro_offset_y = CFG::IMU::accgyro::gyro::def_offset_y;
        gyro_offset_z = CFG::IMU::accgyro::gyro::def_offset_z;
    }
    else
    {
        gyro_offset_x = 0;
        gyro_offset_y = 0;
        gyro_offset_z = 0;
        for (int i = 1; i <= CFG::IMU::accgyro::gyro::offset_calc_sample_n; i++)
        {
            read_raw_datas();
            gyro_offset_x += gyro_raw_x;
            gyro_offset_y += gyro_raw_y;
            gyro_offset_z += gyro_raw_z;
            delayMicroseconds(CFG::IMU::accgyro::gyro::offset_delay);
        }
        gyro_offset_x /= CFG::IMU::accgyro::gyro::offset_calc_sample_n;
        gyro_offset_y /= CFG::IMU::accgyro::gyro::offset_calc_sample_n;
        gyro_offset_z /= CFG::IMU::accgyro::gyro::offset_calc_sample_n;

        //dout << CFG::IMU::msg::gyro_offs_cal_result << "\t" << gyro_offset_x << "\t" << gyro_offset_y << "\t"
             << gyro_offset_z << "\n";
    }

    read_raw_datas();
    calc_acc();
    angle_x = acc_x;
    angle_y = acc_y;
    angle_x_dam = angle_x;
    angle_y_dam = angle_y;
    calc_magn();
    angle_z = compass_heading;

    delayMicroseconds(CFG::IMU::init_delays);
}

void imu_control::init_fast()
{
    timer_s.set_new_timestamp(1);
}

void imu_control::read_raw_datas()
{
    i2c1_mng.i2cRead(CFG::IMU::accgyro::read_raw_reg_addr, 14, CFG::IMU::accgyro::I2C_address);
    acc_raw_x = (int16_t)((i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1]);
    acc_raw_y = (int16_t)((i2c1_mng.i2cData[2] << 8) | i2c1_mng.i2cData[3]);
    acc_raw_z = (int16_t)((i2c1_mng.i2cData[4] << 8) | i2c1_mng.i2cData[5]);
    temp_raw = (int16_t)((i2c1_mng.i2cData[6] << 8) | i2c1_mng.i2cData[7]);
    gyro_raw_x = (int16_t)((i2c1_mng.i2cData[8] << 8) | i2c1_mng.i2cData[9]);
    gyro_raw_y = (int16_t)((i2c1_mng.i2cData[10] << 8) | i2c1_mng.i2cData[11]);
    gyro_raw_z = (int16_t)((i2c1_mng.i2cData[12] << 8) | i2c1_mng.i2cData[13]);

    i2c_mng.i2cRead(CFG::IMU::magneto::read_raw_reg_addr, 6, CFG::IMU::magneto::I2C_address);
    mag_raw_y = (int16_t)((i2c_mng.i2cData[0] << 8) | i2c_mng.i2cData[1]);
    mag_raw_z = (int16_t)((i2c_mng.i2cData[2] << 8) | i2c_mng.i2cData[3]);
    mag_raw_x = (int16_t)((i2c_mng.i2cData[4] << 8) | i2c_mng.i2cData[5]);
}

void imu_control::update()
{
    timer_s.begin();

    dt = timer_s.get_time_since_timestamp(1);
    dt = (double)dt / 1000000;
    timer_s.set_new_timestamp(1);

    read_raw_datas();

    calc_acc();
    calc_gyro();
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

void imu_control::calc_acc()
{
    acc_raw_x -= CFG::IMU::accgyro::acc::offset_x;
    acc_raw_y -= CFG::IMU::accgyro::acc::offset_y;

    acc_raw_x = -acc_raw_x;
    acc_raw_z = -acc_raw_z;
    acc_raw_y = -acc_raw_y;

    new_acc_x = atan(acc_raw_y / sqrt(acc_raw_x * acc_raw_x + acc_raw_z * acc_raw_z)) * RAD_TO_DEG;
    new_acc_y = atan(-acc_raw_x / sqrt(acc_raw_y * acc_raw_y + acc_raw_z * acc_raw_z)) * RAD_TO_DEG;

    if (!isnan(new_acc_x) && !isnan(new_acc_y))
    {
        acc_x = new_acc_x;
        acc_y = new_acc_y;
    }

    /*Serial.print(acc_x); Serial.print("\t");
    Serial.print(acc_y); Serial.print("\t");
    Serial.println("");*/
}

void imu_control::calc_gyro()
{
    gyro_raw_x -= gyro_offset_x;
    gyro_raw_y -= gyro_offset_y;
    gyro_raw_z -= gyro_offset_z;

    gyro_transfer_x = (double)gyro_raw_x / CFG::IMU::accgyro::gyro::sensitivity_scale * dt;
    gyro_transfer_y = (double)gyro_raw_y / CFG::IMU::accgyro::gyro::sensitivity_scale * dt;
    gyro_transfer_z = (double)gyro_raw_z / CFG::IMU::accgyro::gyro::sensitivity_scale * dt;

    /*if (abs(compAngleX) > 90)
          gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
    */
}

void imu_control::calc_compl()
{
    angle_x += gyro_transfer_x;
    angle_y += gyro_transfer_y;
    angle_z += gyro_transfer_z;

    angle_y += angle_x * sin(gyro_transfer_z * PI / 180);
    angle_x -= angle_y * sin(gyro_transfer_z * PI / 180);

    angle_x = CFG::IMU::accgyro::compl_filter_alpha * (angle_x) + CFG::IMU::accgyro::compl_filter_1malpha * acc_x;
    angle_y = CFG::IMU::accgyro::compl_filter_alpha * (angle_y) + CFG::IMU::accgyro::compl_filter_1malpha * acc_y;

    angle_x_dam = CFG::IMU::accgyro::dampen_ang_alpha * (angle_x_dam) + CFG::IMU::accgyro::dampen_ang_1malpha * angle_x;
    angle_y_dam = CFG::IMU::accgyro::dampen_ang_alpha * (angle_y_dam) + CFG::IMU::accgyro::dampen_ang_1malpha * angle_y;
}

void imu_control::calc_magn()
{
    mag_raw_x = -mag_raw_x;

    mag_corr_x = (double)((double)mag_raw_x - (CFG::IMU::magneto::offset_x)) * (CFG::IMU::magneto::scale_x);
    mag_corr_y = (double)((double)mag_raw_y - (CFG::IMU::magneto::offset_y)) * (CFG::IMU::magneto::scale_y);
    mag_corr_z = (double)((double)mag_raw_z - (CFG::IMU::magneto::offset_z)) * (CFG::IMU::magneto::scale_z);

    mag_real_x = mag_corr_x * cos(get_pitch() * PI / 180) +
                 mag_corr_y * sin(get_roll() * PI / 180) * sin(get_pitch() * PI / 180) +
                 mag_corr_z * cos(get_roll() * PI / 180) * sin(get_pitch() * PI / 180);
    mag_real_y = mag_corr_y * cos(get_roll() * PI / 180) - mag_corr_z * sin(get_roll() * PI / 180);

    if (mag_real_x == 0 && mag_real_y < 0)
        compass_heading = 90;
    else if (mag_real_x == 0 && mag_real_y > 0)
        compass_heading = 270;
    else if (mag_real_x < 0)
        compass_heading = (double)180 - (double)atan((double)mag_real_y / mag_real_x) * 180 / PI;
    else if (mag_real_x > 0 && mag_real_y < 0)
        compass_heading = (double)-(double)atan((double)mag_real_y / mag_real_x) * 180 / PI;
    else if (mag_real_x > 0 && mag_real_y > 0)
        compass_heading = (double)360 - (double)atan((double)mag_real_y / mag_real_x) * 180 / PI;
}

void imu_control::yaw_fusion()
{

    angle_z = CFG::IMU::yaw_fusion_alpha * angle_z +
              CFG::IMU::yaw_fusion_1malpha * (angle_z + course_deviation(angle_z, compass_heading));
    // angle_z = angle_z + course_deviation(angle_z, compass_heading) / 1200; //Joop formula

    if (angle_z < 0)
        angle_z = (double)360 + angle_z;
    if (angle_z >= 360)
        angle_z = angle_z - (double)360;
}

double imu_control::course_deviation(double course_c, double course_b)
{
    double course_a = course_b - course_c;
    float base_course_mirrored, actual_course_mirrored;
    if (course_a < -180 || course_a > 180)
    {
        if (course_c > 180)
            base_course_mirrored = course_c - 180;
        else
            base_course_mirrored = course_c + 180;
        if (course_b > 180)
            actual_course_mirrored = course_b - 180;
        else
            actual_course_mirrored = course_b + 180;
        course_a = actual_course_mirrored - base_course_mirrored;
    }
    return course_a;
}

double imu_control::get_roll()
{
    return angle_x_dam;
}

double imu_control::get_pitch()
{
    return angle_y_dam;
}

double imu_control::get_yaw()
{
    return angle_z;
}

double imu_control::get_temp()
{
    return temp;
}