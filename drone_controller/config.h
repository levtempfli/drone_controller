#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

//ESC Controller - escct
constexpr uint16_t ESCCT_MINTHROTTLE = 100;
constexpr uint16_t ESCCT_MAXTHROTTLE = 900;
constexpr uint8_t ESCCT_ESC1PIN = 2;
constexpr uint8_t ESCCT_ESC2PIN = 3;
constexpr uint8_t ESCCT_ESC3PIN = 4;
constexpr uint8_t ESCCT_ESC4PIN = 5;

constexpr uint64_t ESCCT_TIMER_BEGINTIME = 4250;
constexpr uint64_t ESCCT_TIMER_ENDTIME = 4300;
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



#endif // !CONFIG_H

