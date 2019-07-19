#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>
#include <Arduino.h>

//ESC Controller - escct
constexpr uint16_t ESCCT_MINTHROTTLE = 100;
constexpr uint16_t ESCCT_MAXTHROTTLE = 900;
constexpr uint8_t ESCCT_ESC1PIN = 5;
constexpr uint8_t ESCCT_ESC2PIN = 2;
constexpr uint8_t ESCCT_ESC3PIN = 3;
constexpr uint8_t ESCCT_ESC4PIN = 4;
constexpr uint32_t ESCCT_INIT_WAIT_TIME = 5000000;

constexpr uint64_t ESCCT_TIMER_BEGINTIME = 4120;
constexpr uint64_t ESCCT_TIMER_ENDTIME = 4200;
constexpr bool ESCCT_TIMER_BEGINBLOCK = 1;
constexpr bool ESCCT_TIMER_ENDBLOCK = 1;
constexpr uint64_t ESCCT_TIMER_WARNINGTIME = 4300;

//MAIN TIMER - timer_main
constexpr bool TIMER_MAIN_ENDBLOCK = 1;
constexpr uint64_t TIMER_MAIN_TURNTOTAL = 4000;
constexpr uint8_t TIMER_SUB_TS_ARRAYLENGTH = 5;

//I2C manager - i2c_manager
constexpr bool I2C_MANAGER_RELEASEBUS = 0;
constexpr uint8_t I2C_MANAGER_MAXDATALENGTH = 15;
constexpr uint32_t I2C_MANAGER_CLOCK = 400000;

//I2C1 manager - i2c1_manager
constexpr bool I2C1_MANAGER_RELEASEBUS = 0;
constexpr uint8_t I2C1_MANAGER_MAXDATALENGTH = 15;
constexpr uint32_t I2C1_MANAGER_CLOCK = 400000;

//IMU - imu
constexpr uint8_t IMU_ACGY_I2C_ADDRESS = 0x68;
constexpr uint8_t IMU_MAGN_I2C_ADDRESS = 0x1E;
constexpr uint8_t IMU_ACGY_WHO_AM_I = 0x75;
constexpr uint8_t IMU_MAGN_IDEN_STADR = 0X0A;//3 registers are read
constexpr int32_t IMU_MAGN_IDEN_VAL = 4731955;
constexpr uint64_t IMU_INIT_DELAY_SHORT = 100000;
constexpr uint8_t IMU_ACGY_CONFIG_N = 4;
constexpr uint8_t IMU_ACGY_CONFIG_REGADR[IMU_ACGY_CONFIG_N] = { 0x6B, 0x1B, 0x1C, 0x1A };
constexpr uint8_t IMU_ACGY_CONFIG_REGVAL[IMU_ACGY_CONFIG_N] = { 0x00, 0x08 ,0x10, 0x03 };
constexpr uint8_t IMU_MAGN_CONFIG_N = 3;
constexpr uint8_t IMU_MAGN_CONFIG_REGADR[IMU_ACGY_CONFIG_N] = { 0x00, 0x01, 0x02 };
constexpr uint8_t IMU_MAGN_CONFIG_REGVAL[IMU_ACGY_CONFIG_N] = { 0x78, 0x20 ,0x00 };//Regiser A bits as 01111000 to set sample rate (average of 8 at 75Hz). Regiser B bits as 00100000 to set the gain at +/-1.3Ga.  Mode Regiser bits as 00000000 to set Continues-Measurement Mode. 
constexpr uint8_t IMU_ACGY_READRAW_REGVAL = 0x3B;//14 values are read
constexpr double IMU_GYR_OFFSET_X = -91.92;
constexpr double IMU_GYR_OFFSET_Y = -62.97;
constexpr double IMU_GYR_OFFSET_Z = -48.52;
constexpr int16_t IMU_ACC_OFFSET_X = 279;
constexpr int16_t IMU_ACC_OFFSET_Y = -70;
constexpr bool IMU_GYRO_INIT_OFFSETCALC = 1;
constexpr uint16_t IMU_GYRO_INIT_OFFSET_SAMPLE_N = 2000;
constexpr uint64_t IMU_GYRO_INIT_OFFSET_DELAY = 500;
constexpr uint8_t IMU_GYRO_SENSITIVITY_SCALE = 65.5;
constexpr double IMU_COMPL_FILTER_ALFA = 0.98;
constexpr double IMU_COMPL_FILTER_1MALFA = 0.02;
constexpr double IMU_DAMPEN_ANG_ALFA = 0.9;
constexpr double IMU_DAMPEN_ANG_1MALFA = 0.1;
constexpr uint8_t IMU_MAGN_READRAW_REGVAL = 0x03;//6 values are read
constexpr double IMU_MAGN_OFFSET_X = -126;
constexpr double IMU_MAGN_OFFSET_Y = -0.5;
constexpr double IMU_MAGN_OFFSET_Z = 128;
constexpr double IMU_MAGN_SCALE_X = 1.068181818;
constexpr double IMU_MAGN_SCALE_Y = 0.887947883;
constexpr double IMU_MAGN_SCALE_Z = 1.066510172;
constexpr double IMU_YAW_FUSION_ALFA = 0.98;
constexpr double IMU_YAW_FUSION_1MALFA = 0.02;
constexpr uint64_t IMU_TIMER_BEGINTIME = 2500;
constexpr uint64_t IMU_TIMER_ENDTIME = 3850;
constexpr bool IMU_TIMER_BEGINBLOCK = 1;
constexpr bool IMU_TIMER_ENDBLOCK = 1;
constexpr uint64_t IMU_TIMER_WARNINGTIME = 3700;


//Battery monitor - battery_monitor
constexpr uint64_t BTM_TIMER_BEGINTIME = 4000;
constexpr uint64_t BTM_TIMER_ENDTIME = 4100;
constexpr bool BTM_TIMER_BEGINBLOCK = 1;
constexpr bool BTM_TIMER_ENDBLOCK = 1;
constexpr uint64_t BTM_TIMER_WARNINGTIME = 4050;
constexpr double BTM_VLT_CONV_VAL = 10.210;
constexpr double BTM_CUR_CONV_VAL = 27.3322;
constexpr double BTM_VLT_COMPL_FILTER_ALFA = 0.95;
constexpr double BTM_VLT_COMPL_FILTER_1MALFA = 0.05;
constexpr double BTM_CUR_COMPL_FILTER_ALFA = 0.95;
constexpr double BTM_CUR_COMPL_FILTER_1MALFA = 0.05;
constexpr uint8_t BTM_VLT_SENSOR_PIN = A3;
constexpr uint8_t BTM_CUR_SENSOR_PIN = A2;
constexpr double BTM_COMP_REF_VLT = 12.40;
constexpr double BTM_COMP_VAL = 40;
constexpr double BTM_BAT_100PER_VLT = 12.60;
constexpr double BTM_BAT_0PER_VLT = 10.50;
constexpr uint16_t BTM_BAT_MAH = 10000;

//GPS - GPS NMEA decoder

constexpr uint16_t GPS_BUFF_SIZE = 100;
constexpr uint16_t GPS_CFG_DENMEA_MSGL = 11;
constexpr uint16_t GPS_CFG_SB_MSGL = 28;
constexpr uint16_t GPS_CFG_SR_MSGL = 14;
constexpr uint8_t GPS_CFG_SET_BAUD[GPS_CFG_SB_MSGL] = { 0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0x08, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xD4 }; //Set baud rate to 460800
constexpr uint8_t GPS_CFG_DISABLE_GGA[GPS_CFG_DENMEA_MSGL] = { 0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x00, 0x00, 0xFA, 0x0F }; //disable GGA messages
constexpr uint8_t GPS_CFG_DISABLE_GLL[GPS_CFG_DENMEA_MSGL] = { 0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x01, 0x00, 0xFB, 0x11 }; //disable GLL messages
constexpr uint8_t GPS_CFG_DISABLE_GSV[GPS_CFG_DENMEA_MSGL] = { 0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x03, 0x00, 0xFD, 0x15 }; //disable GSV messages
constexpr uint8_t GPS_CFG_DISABLE_TXT[GPS_CFG_DENMEA_MSGL] = { 0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x41, 0x00, 0x3B, 0x91 }; //disable TXT messages
constexpr uint8_t GPS_CFG_DISABLE_RMC[GPS_CFG_DENMEA_MSGL] = { 0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x04, 0x00, 0xFE, 0x17 }; //disable RMC messages
constexpr uint8_t GPS_CFG_ENABLE_VTG[GPS_CFG_DENMEA_MSGL] = { 0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x05, 0x01, 0x00, 0x1A }; //disable VTG messages
constexpr uint8_t GPS_CFG_ENABLE_GNS[GPS_CFG_DENMEA_MSGL] = { 0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x0D, 0x01, 0x08, 0x2A }; //disable GNS messages
constexpr uint8_t GPS_CFG_ENABLE_GSA[GPS_CFG_DENMEA_MSGL] = { 0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x02, 0x01, 0xFD, 0x14 }; //disable GSA messages
constexpr uint8_t GPS_CFG_SET_RATE[GPS_CFG_SR_MSGL] = { 0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xC8, 0x00, 0x01, 0x00, 0x01, 0x00, 0xDE, 0x6A }; //set rate to 5hz (200ms)
constexpr uint64_t GPS_CFG_DELAY = 300000;
constexpr uint64_t GPS_INIT_DELAY = 3000000;
constexpr uint32_t GPS_ST_SERIAL_BAUD = 9600;
constexpr uint32_t GPS_SERIAL_BAUD = 460800;
constexpr uint64_t GPS_TIMEOUT = 400000;
constexpr uint64_t GPS_TIMER_BEGINTIME = 1900;
constexpr uint64_t GPS_TIMER_ENDTIME = 2350;
constexpr bool GPS_TIMER_BEGINBLOCK = 1;
constexpr bool GPS_TIMER_ENDBLOCK = 1;
constexpr uint64_t GPS_TIMER_WARNINGTIME = 2275;


//Debug messages
constexpr char DBG_IMU_ACGY_INIT_ERROR[] = "IMU - INIT - Error at communication with the accelerometer & gyroscope";
constexpr char DBG_IMU_MAGN_INIT_ERROR[] = "IMU - INIT - Error at communication with the magnetometer";
constexpr char DBG_IMU_OFFSCAL_RESULT[] = "IMU - INIT - New gyro calculated offsets(XYZ):";

#endif // !CONFIG_H

