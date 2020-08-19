#include "config.h"

const uint8_t CFG::GPS::settings::set_baud_msg[CFG::GPS::settings::set_baud_msg_len] = {
    0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00,
    0x00, 0x08, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xD4}; // Set baud rate to 460800
const uint8_t CFG::GPS::settings::disable_GGA[CFG::GPS::settings::denmea_msg_len] = {
    0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x00, 0x00, 0xFA, 0x0F}; // disable GGA messages
const uint8_t CFG::GPS::settings::disable_GLL[CFG::GPS::settings::denmea_msg_len] = {
    0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x01, 0x00, 0xFB, 0x11}; // disable GLL messages
const uint8_t CFG::GPS::settings::disable_GSV[CFG::GPS::settings::denmea_msg_len] = {
    0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x03, 0x00, 0xFD, 0x15}; // disable GSV messages
const uint8_t CFG::GPS::settings::disable_TXT[CFG::GPS::settings::denmea_msg_len] = {
    0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x41, 0x00, 0x3B, 0x91}; // disable TXT messages
const uint8_t CFG::GPS::settings::disable_RMC[CFG::GPS::settings::denmea_msg_len] = {
    0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x04, 0x00, 0xFE, 0x17}; // disable RMC messages
const uint8_t CFG::GPS::settings::enable_VTG[CFG::GPS::settings::denmea_msg_len] = {
    0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x05, 0x01, 0x00, 0x1A}; // enable VTG messages
const uint8_t CFG::GPS::settings::enable_GNS[CFG::GPS::settings::denmea_msg_len] = {
    0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x0D, 0x01, 0x08, 0x2A}; // enable GNS messages
const uint8_t CFG::GPS::settings::enable_GSA[CFG::GPS::settings::denmea_msg_len] = {
    0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x02, 0x01, 0xFD, 0x14}; // enable GSA messages
const uint8_t CFG::GPS::settings::set_rate_msg[CFG::GPS::settings::set_rate_msg_len] = {
    0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xC8, 0x00, 0x01, 0x00, 0x01, 0x00, 0xDE, 0x6A}; // set rate to 5hz (200ms)

const uint8_t CFG::IMU::accgyro::settings_reg_addr[CFG::IMU::accgyro::settings_n] = {0x6B, 0x1B, 0x1C, 0x1A};
const uint8_t CFG::IMU::accgyro::settings_reg_val[CFG::IMU::accgyro::settings_n] = {0x00, 0x08, 0x10, 0x03};
const uint8_t CFG::IMU::magneto::settings_reg_addr[CFG::IMU::magneto::settings_n] = {0x00, 0x01, 0x02};
// Regiser A bits as 01111000 to set sample rate (average of 8 at 75Hz). Regiser B bits as 00100000 to set
// the gain at +/-1.3Ga.  Mode Regiser bits as 00000000 to set Continues-Measurement Mode.
const uint8_t CFG::IMU::magneto::settings_reg_val[CFG::IMU::magneto::settings_n] = {0x78, 0x20, 0x00};

const char CFG::IMU::msg::acgy_init_error[] = "IMU - INIT - Error at communication with the accelerometer & gyroscope";
const char CFG::IMU::msg::magn_init_error[] = "IMU - INIT - Error at communication with the magnetometer";
const char CFG::IMU::msg::gyro_offs_cal_result[] = "IMU - INIT - New gyro calculated offsets(XYZ):";
const char CFG::BMP::baro_init_error[] = "BARO - INIT - Error at communication with the barometer";