#include "config.h"

const uint8_t CFG::IMU::accgyro::settings_reg_addr[CFG::IMU::accgyro::settings_n] = {0x6B, 0x1B, 0x1C, 0x1A};
const uint8_t CFG::IMU::accgyro::settings_reg_val[CFG::IMU::accgyro::settings_n] = {0x00, 0x08, 0x10, 0x03};
const uint8_t CFG::IMU::magneto::settings_reg_addr[CFG::IMU::magneto::settings_n] = {0x00, 0x01, 0x02};
// Regiser A bits as 01111000 to set sample rate (average of 8 at 75Hz). Regiser B bits as 00100000 to set
// the gain at +/-1.3Ga.  Mode Regiser bits as 00000000 to set Continues-Measurement Mode.
const uint8_t CFG::IMU::magneto::settings_reg_val[CFG::IMU::magneto::settings_n] = {0x78, 0x20, 0x00};

const char CFG::IMU::msg::acgy_init_error[] = "IMU - INIT - Error at communication with the accelerometer & gyroscope";
const char CFG::IMU::msg::magn_init_error[] = "IMU - INIT - Error at communication with the magnetometer";
const char CFG::IMU::msg::gyro_offs_cal_result[] = "IMU - INIT - New gyro calculated offsets(XYZ):";