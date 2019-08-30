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

constexpr uint64_t ESCCT_TIMER_BEGINTIME = 3700;
constexpr uint64_t ESCCT_TIMER_ENDTIME = 3720;
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

constexpr uint64_t BTM_TIMER_BEGINTIME = 4000;
constexpr uint64_t BTM_TIMER_ENDTIME = 4100;
constexpr bool BTM_TIMER_BEGINBLOCK = 1;
constexpr bool BTM_TIMER_ENDBLOCK = 1;
constexpr uint64_t BTM_TIMER_WARNINGTIME = 4050;

//GPS - GPS NMEA decoder

constexpr uint16_t GPS_BUFF_SIZE = 128;
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
constexpr uint64_t GPS_CFG_DELAY = 200000;
constexpr uint32_t GPS_ST_SERIAL1_BAUD = 9600;
constexpr uint32_t GPS_SERIAL1_BAUD = 460800;
constexpr uint64_t GPS_TIMEOUT = 400000;

constexpr uint64_t GPS_TIMER_BEGINTIME = 2000;
constexpr uint64_t GPS_TIMER_ENDTIME = 2550;
constexpr bool GPS_TIMER_BEGINBLOCK = 1;
constexpr bool GPS_TIMER_ENDBLOCK = 1;
constexpr uint64_t GPS_TIMER_WARNINGTIME = 2275;

//Sonar
constexpr uint16_t SONAR_TRIGGER_PIN = 54;
constexpr uint16_t SONAR_ECHO_PIN = 55;
constexpr uint64_t SONAR_DELAY_AFTER_CLEAR = 2;
constexpr uint64_t SONAR_DELAY_AFTER_TRIGGER = 2;
constexpr uint64_t SONAR_WAIT_FOR_SIGNAL_TIMEOUT = 1500;
constexpr double SONAR_SOUND_DISTANCE_IN_1MS = 0.0343; //cm/ms
constexpr double SONAR_MAX_DISTANCE_FROM_GROUND = 20;
constexpr uint64_t SONAR_DATA_TIMEOUT = 100000;

constexpr uint64_t SONAR_TIMER_BEGINTIME = 1500;
constexpr uint64_t SONAR_TIMER_ENDTIME = 3250;
constexpr bool SONAR_TIMER_BEGINBLOCK = 1;
constexpr bool SONAR_TIMER_ENDBLOCK = 1;
constexpr uint64_t SONAR_TIMER_WARNINGTIME = 3700;

//Barometer - baro
constexpr uint8_t BARO_I2C_ADDR = 0x77;
constexpr uint8_t BARO_MODE = 3;//ultralowpower-0, standard-1, highres-2, ultrahighres-3
constexpr uint64_t BARO_PRES_MEAS_DURATION = 26500;//ultralowpower-4500, standard-7500, highres-13500, ultrahighres-25500
constexpr uint64_t BARO_TEMP_MEAS_DURATION = 4600;
constexpr uint8_t BARO_CAL_AC1 = 0xAA;
constexpr uint8_t BARO_CAL_AC2 = 0xAC;
constexpr uint8_t BARO_CAL_AC3 = 0xAE;
constexpr uint8_t BARO_CAL_AC4 = 0xB0;
constexpr uint8_t BARO_CAL_AC5 = 0xB2;
constexpr uint8_t BARO_CAL_AC6 = 0xB4;
constexpr uint8_t BARO_CAL_B1 = 0xB6;
constexpr uint8_t BARO_CAL_B2 = 0xB8;
constexpr uint8_t BARO_CAL_MB = 0xBA;
constexpr uint8_t BARO_CAL_MC = 0xBC;
constexpr uint8_t BARO_CAL_MD = 0xBE;
constexpr uint8_t BARO_CMD_CONTROL = 0xF4;
constexpr uint8_t BARO_CMD_READTEMP = 0x2E;
constexpr uint8_t BARO_CMD_READPRESS = 0x34;
constexpr uint8_t BARO_DATA = 0xF6;
constexpr uint8_t BARO_CHIPID_REG = 0xD0;
constexpr uint8_t BARO_CHIPID_VAL = 0x55;
constexpr int32_t BARO_DEF_SEALEVELPRESSURE = 101325;
constexpr uint16_t BARO_NUM_OF_AVG = 20;//Number of pressure reading datas to average
constexpr double BARO_COMPL_FILTER_ALFA = 0.985;
constexpr double BARO_COMPL_FILTER_1MALFA = 0.015;
constexpr int32_t BARO_CORR_MAX_DIFF = 8;
constexpr int32_t BARO_CORR_MIN_DIFF = 1;
constexpr double BARO_CORR_ADJ_DIV = 6.0;
constexpr double BARO_ALT_CALC_CONST1 = 44330;
constexpr double BARO_ALT_CALC_CONST2 = 0.1903;

constexpr uint64_t BARO_TIMER_BEGINTIME = 4000;
constexpr uint64_t BARO_TIMER_ENDTIME = 4475;
constexpr bool BARO_TIMER_BEGINBLOCK = 1;
constexpr bool BARO_TIMER_ENDBLOCK = 1;
constexpr uint64_t BARO_TIMER_WARNINGTIME = 4450;

//Communication with the RPI
constexpr uint64_t COM_SERIAL2_BAUD_RATE = 9600;

//Debug
constexpr uint64_t DBG_SERIAL0_BAUD_RATE = 250000;
constexpr uint64_t DBG_SERIAL2_BAUD_RATE = COM_SERIAL2_BAUD_RATE;
constexpr uint64_t DBG_OUT_FATAL_LOOP_WAIT = 100000;
constexpr uint32_t DBG_OUT_BUFFER_LENGTH = 2000;
constexpr int8_t DBG_OUT_MAX_PRECISION = 8;
constexpr int8_t DBG_OUT_DEF_PRECISION = 2;
constexpr int8_t DBG_OUT_DEF_ROUND_MODE = 2;//1-floor, 2-round
constexpr uint32_t DBG_IN_BUFFER_LENGTH = 2000;
constexpr uint64_t DBG_IN_PARSE_WAITIME = 300;
constexpr uint64_t DBG_IN_READ_SERIAL_BYTE_DELAY = 150;//12/250000*1000000=48*3~150

//Debug messages
constexpr char DBG_IMU_ACGY_INIT_ERROR[] = "IMU - INIT - Error at communication with the accelerometer & gyroscope";
constexpr char DBG_IMU_MAGN_INIT_ERROR[] = "IMU - INIT - Error at communication with the magnetometer";
constexpr char DBG_IMU_OFFSCAL_RESULT[] = "IMU - INIT - New gyro calculated offsets(XYZ):";
constexpr char DBG_BARO_INIT_ERROR[] = "BARO - INIT - Error at communication with the barometer";

#endif // !CONFIG_H

