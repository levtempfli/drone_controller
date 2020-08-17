#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#include <stdint.h>
struct Telem_Data
{
    int32_t pressure = 0;
    double temperature = 0;
    double baro_alti = 0;
    int32_t GPS_lat = 0;
    int32_t GPS_lon = 0;
    double GPS_alt = 0;
    int8_t GPS_fix = 0;
    double GPS_speed = 0;
    int8_t GPS_sats = 0;
    double GPS_PDOP = 0;
    int32_t home_lat = 0;
    int32_t home_lon = 0;
    int32_t lat_set = 0;
    int32_t lon_set = 0;
    double alt_set = 0;
    double IMUX_set = 0;
    double IMUY_set = 0;
    double IMUZ_set = 0;
    double IMUX = 0;
    double IMUY = 0;
    double IMUZ = 0;
    double volt = 0;
    double curr = 0;
    double est_bat = 0;
    double est_rem = 0;
    int8_t mode = 1;
    double sonar_dist = 0;
    long I2C_err = 0;
    long timer_err = 0;
};

struct Control_Data
{
    short mode_set = 1;
    short control_x = 0;
    short control_y = 0;
    short control_zr = 0;
    short control_a = 0;
    short control_s = 0;
};

#endif // !DATA_STRUCTS_H
