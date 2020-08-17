#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>
#include <Arduino.h>

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

//Serial Raspberry Pi
constexpr uint64_t SER_SERIAL2_BAUD_RATE = 115200;//460800
constexpr uint32_t SER_INBUFF_SIZE = 64000;
constexpr uint32_t SER_OUTBUFF_SIZE = 256;
constexpr uint32_t SER_SLVBUFF_SIZE = 4098;
constexpr uint64_t SER_CONN_MSG_TIMEOUT = 5000000;
constexpr uint64_t SER_SEND_PERIOD = 100000;
constexpr uint8_t SER_MSG_TYPES_MAX = 3;

constexpr uint64_t SER_TIMER_BEGINTIME = 1500;
constexpr uint64_t SER_TIMER_ENDTIME = 2000;
constexpr bool SER_TIMER_BEGINBLOCK = 1;
constexpr bool SER_TIMER_ENDBLOCK = 1;
constexpr uint64_t SER_TIMER_WARNINGTIME = 1900;

//Debug messages
constexpr char DBG_IMU_ACGY_INIT_ERROR[] = "IMU - INIT - Error at communication with the accelerometer & gyroscope";
constexpr char DBG_IMU_MAGN_INIT_ERROR[] = "IMU - INIT - Error at communication with the magnetometer";
constexpr char DBG_IMU_OFFSCAL_RESULT[] = "IMU - INIT - New gyro calculated offsets(XYZ):";
constexpr char DBG_BARO_INIT_ERROR[] = "BARO - INIT - Error at communication with the barometer";

#endif // !CONFIG_H

