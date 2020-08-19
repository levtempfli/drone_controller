#ifndef BARO_H
#define BARO_H

#include "I2C1_manager.h"
#include "debug_in.h"
#include "debug_out.h"
#include "timer_sub.h"
#include <stdint.h>

class bmp_180
{
  public:
    bmp_180(timer_main &tm, i2c1_manager &i2c1m, debug_out &dou); // Constructor
    bmp_180() = delete;
    bmp_180(const bmp_180 &) = delete;

    void init();
    void set_altitude(double altitude);
    void update();
    double get_pressure(uint8_t mode = 1);
    double get_temperature();
    double get_altitude();
    bool is_there_new_pressure();

  private:
    timer_sub timer_s;
    timer_main &timer_m;
    i2c1_manager &i2c1_mng;
    debug_out &dout;

    int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
    uint16_t ac4, ac5, ac6;
    uint8_t oversampling;
    int32_t UT, B5;
    int32_t pressure;
    int32_t sealevelpressure;
    int32_t rot_mem[CFG::BMP::num_of_avg];
    int16_t rot_mem_i;
    int32_t rot_sum;
    double rot_avg;
    double compl_1_corr, compl_2;
    bool curr_measurement; // 0-temperature 1-pressure
    bool new_pressure_data;
    double altitude;
    double temp;
    void start_temp();
    void start_press();
    void read_temp();
    void read_press();
    void calc_altitude();
};

#endif // !BARO_H
