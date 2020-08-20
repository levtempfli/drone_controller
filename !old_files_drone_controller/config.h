#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>
#include <Arduino.h>

//Sonar



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

#endif // !CONFIG_H

