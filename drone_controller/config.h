#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>
#include <Arduino.h>

//ESC Controller - escct
constexpr uint16_t ESCCT_MINTHROTTLE = 100;
constexpr uint16_t ESCCT_MAXTHROTTLE = 900;
constexpr uint8_t ESCCT_ESC1PIN = 2;
constexpr uint8_t ESCCT_ESC2PIN = 3;
constexpr uint8_t ESCCT_ESC3PIN = 4;
constexpr uint8_t ESCCT_ESC4PIN = 5;
constexpr uint32_t ESCCT_INIT_WAIT_TIME = 5000000;

constexpr uint64_t ESCCT_TIMER_BEGINTIME = 4120;
constexpr uint64_t ESCCT_TIMER_ENDTIME = 4200;
constexpr bool ESCCT_TIMER_BEGINBLOCK = 1;
constexpr bool ESCCT_TIMER_ENDBLOCK = 1;
constexpr uint64_t ESCCT_TIMER_WARNINGTIME = 4300;

//MAIN TIMER - timer_main
constexpr bool TIMER_MAIN_ENDBLOCK = 1;
constexpr uint64_t TIMER_MAIN_TURNTOTAL = 5000;
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
constexpr uint8_t IMU_I2C_ADDRESS = 0x68;
constexpr uint8_t IMU_WHO_AM_I = 0x75;
constexpr uint8_t IMU_CONFIG_N = 5;
constexpr uint8_t IMU_CONFIG_REGADR[IMU_CONFIG_N] = { 0x19, 0x1A, 0x1B, 0x1C, 0x6B };
constexpr uint8_t IMU_CONFIG_REGVAL[IMU_CONFIG_N] = { 0x07, 0x00, 0x00 ,0x00 ,0x01 };
constexpr double IMU_DEFGOFFSET_X= -127.28;
constexpr double IMU_DEFGOFFSET_Y= -112.68;
constexpr double IMU_DEFGOFFSET_Z= -19.95;
constexpr bool IMU_INIT_OFFSETCALC = 1;
constexpr uint16_t IMU_INIT_OFFSET_SAMPLE_N = 2000;
constexpr uint8_t IMU_GYRO_SENSITIVITY_SCALE = 131;
constexpr double IMU_COMPL_FILTER_ALFA = 0.93;
constexpr double IMU_COMPL_FILTER_1MALFA = 0.07;
constexpr uint64_t IMU_TIMER_BEGINTIME = 3000;
constexpr uint64_t IMU_TIMER_ENDTIME = 4000;
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


//Debug messages
constexpr char DBG_IMU_INIT_ERROR[] = "IMU - INIT - Error at communication with the sensor";
constexpr char DBG_IMU_OFFSCAL_RESULT[] = "IMU - INIT - New gyro calculated offsets(XYZ):";

#endif // !CONFIG_H
