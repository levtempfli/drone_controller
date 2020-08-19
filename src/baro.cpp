#include "baro.h"

bmp_180::bmp_180(timer_main &tm, i2c1_manager &i2c1m, debug_out &dou)
    : timer_s(CFG::BMP::timer::begin_time, CFG::BMP::timer::end_time, CFG::BMP::timer::begin_block,
              CFG::BMP::timer::end_block, CFG::BMP::timer::warning_time, tm),
      timer_m(tm), i2c1_mng(i2c1m), dout(dou)
{
}

void bmp_180::init()
{
    oversampling = CFG::BMP::mode;
    sealevelpressure = CFG::BMP::def_sealevel_pressure;

    i2c1_mng.i2cRead(CFG::BMP::i2c::chipid_reg, 1, CFG::BMP::i2c::address);

    if (i2c1_mng.i2cData[0] != CFG::BMP::i2c::chipid_val)
    {
        dout.fatal_error(CFG::BMP::baro_init_error);
    }

    i2c1_mng.i2cRead(CFG::BMP::cal::ac1, 2, CFG::BMP::i2c::address);
    ac1 = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];
    i2c1_mng.i2cRead(CFG::BMP::cal::ac2, 2, CFG::BMP::i2c::address);
    ac2 = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];
    i2c1_mng.i2cRead(CFG::BMP::cal::ac3, 2, CFG::BMP::i2c::address);
    ac3 = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];
    i2c1_mng.i2cRead(CFG::BMP::cal::ac4, 2, CFG::BMP::i2c::address);
    ac4 = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];
    i2c1_mng.i2cRead(CFG::BMP::cal::ac5, 2, CFG::BMP::i2c::address);
    ac5 = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];
    i2c1_mng.i2cRead(CFG::BMP::cal::ac6, 2, CFG::BMP::i2c::address);
    ac6 = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];
    i2c1_mng.i2cRead(CFG::BMP::cal::b1, 2, CFG::BMP::i2c::address);
    b1 = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];
    i2c1_mng.i2cRead(CFG::BMP::cal::b2, 2, CFG::BMP::i2c::address);
    b2 = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];
    i2c1_mng.i2cRead(CFG::BMP::cal::mb, 2, CFG::BMP::i2c::address);
    mb = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];
    i2c1_mng.i2cRead(CFG::BMP::cal::mc, 2, CFG::BMP::i2c::address);
    mc = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];
    i2c1_mng.i2cRead(CFG::BMP::cal::md, 2, CFG::BMP::i2c::address);
    md = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];

    rot_sum = 0;
    for (int i = 0; i < CFG::BMP::num_of_avg; i++)
    {
        start_temp();
        delayMicroseconds(CFG::BMP::temp_meas_duration);
        read_temp();

        start_press();
        delayMicroseconds(CFG::BMP::press_meas_duration);
        read_press();

        rot_mem[i] = pressure;
        rot_sum += pressure;
    }

    rot_mem_i = 1;
    rot_avg = rot_sum / CFG::BMP::num_of_avg;

    compl_2 = rot_avg;
    compl_1_corr = rot_avg;

    calc_altitude();

    start_temp();
    timer_s.set_new_timestamp(0);
    curr_measurement = 0;
}

void bmp_180::start_temp()
{
    i2c1_mng.i2cData[0] = CFG::BMP::i2c::cmd_readtemp;
    i2c1_mng.i2cWrite(CFG::BMP::i2c::cmd_control_reg, 1, CFG::BMP::i2c::address);
}

void bmp_180::start_press()
{
    i2c1_mng.i2cData[0] = CFG::BMP::i2c::cmd_readpress + (oversampling << 6);
    i2c1_mng.i2cWrite(CFG::BMP::i2c::cmd_control_reg, 1, CFG::BMP::i2c::address);
}

void bmp_180::read_temp()
{
    i2c1_mng.i2cRead(CFG::BMP::i2c::data_reg, 2, CFG::BMP::i2c::address);
    UT = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];
    int32_t Y1 = (UT - (int32_t)ac6) * ((int32_t)ac5) >> 15;
    int32_t Y2 = ((int32_t)mc << 11) / (Y1 + (int32_t)md);
    B5 = Y1 + Y2;
    temp = (B5 + 8) >> 4;
    temp /= 10;
}

void bmp_180::read_press()
{
    uint32_t raw;
    int32_t UP, B3, B6, X1, X2, X3;
    uint32_t B4, B7;

    i2c1_mng.i2cRead(CFG::BMP::i2c::data_reg, 3, CFG::BMP::i2c::address);
    raw = (i2c1_mng.i2cData[0] << 8) | i2c1_mng.i2cData[1];

    raw <<= 8;
    raw |= i2c1_mng.i2cData[2];
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

    if (B7 < 0x80000000)
    {
        pressure = (B7 * 2) / B4;
    }
    else
    {
        pressure = (B7 / B4) * 2;
    }
    X1 = (pressure >> 8) * (pressure >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * pressure) >> 16;

    pressure = pressure + ((X1 + X2 + (int32_t)3791) >> 4);
}

void bmp_180::calc_altitude()
{
    altitude = (double)CFG::BMP::alt_calc_const1 *
               (1.0 - pow(compl_1_corr / (double)sealevelpressure, CFG::BMP::alt_calc_const2));
}

void bmp_180::set_altitude(double new_altitude)
{
    sealevelpressure =
        (int32_t)(compl_1_corr / pow(1.0 - new_altitude / CFG::BMP::alt_calc_const1, (1 / CFG::BMP::alt_calc_const2)));
    calc_altitude();
}

void bmp_180::update()
{
    timer_s.begin();

    if (new_pressure_data == 1)
        new_pressure_data = 0;

    if (curr_measurement == 0)
    {
        // delayMicroseconds(CFG::BMP::temp_meas_duration);
        if (timer_s.get_time_since_timestamp(0) >= CFG::BMP::temp_meas_duration)
        {
            read_temp();
            start_press();
            timer_s.set_new_timestamp(1);
            curr_measurement = 1;
        }
    }
    if (curr_measurement == 1)
    {
        // delayMicroseconds(CFG::BMP::press_meas_duration);
        if (timer_s.get_time_since_timestamp(1) >= CFG::BMP::press_meas_duration)
        {
            read_press();
            new_pressure_data = 1;
            start_temp();
            timer_s.set_new_timestamp(0);
            curr_measurement = 0;
        }
    }

    if (new_pressure_data)
    {
        rot_sum = rot_sum - rot_mem[rot_mem_i];
        rot_mem[rot_mem_i] = pressure;
        rot_sum = rot_sum + rot_mem[rot_mem_i];
        rot_mem_i++;
        if (rot_mem_i == CFG::BMP::num_of_avg - 1)
            rot_mem_i = 0;
        rot_avg = (double)rot_sum / CFG::BMP::num_of_avg;

        compl_2 = CFG::BMP::compl_filter_alpha * compl_2 + CFG::BMP::compl_filter_1malpha * rot_avg;
        compl_1_corr = CFG::BMP::compl_filter_alpha * compl_1_corr + CFG::BMP::compl_filter_1malpha * rot_avg;

        double actual_pressure_diff = compl_1_corr - rot_avg;
        if (actual_pressure_diff > CFG::BMP::corr_max_diff)
            actual_pressure_diff =
                CFG::BMP::corr_max_diff; // If the difference is larger then 8 limit the difference to 8.
        if (actual_pressure_diff < -CFG::BMP::corr_max_diff)
            actual_pressure_diff =
                -CFG::BMP::corr_max_diff; // If the difference is smaller then -8 limit the difference to -8.
        if (actual_pressure_diff > CFG::BMP::corr_min_diff || actual_pressure_diff < -CFG::BMP::corr_min_diff)
            compl_1_corr -=
                actual_pressure_diff /
                CFG::BMP::corr_adjust_div; // If the difference is larger then 1 or smaller then -1 the slow average
                                           // is adjuste based on the error between the fast and slow average.

        calc_altitude();
    }

    timer_s.end();
}

double bmp_180::get_pressure(uint8_t mode)
{ // 1(default)-Corrected data(average & complementary fusion), 2-average data, 3-complementary data, 4-raw data
    switch (mode)
    {
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

double bmp_180::get_temperature()
{
    return temp;
}

double bmp_180::get_altitude()
{
    return altitude;
}

bool bmp_180::is_there_new_pressure()
{
    return new_pressure_data;
}
