#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

// Configurations
struct CFG
{

    // I2C manager configs
    struct I2C_man
    {
        static const bool release_bus = 0;
        static const uint8_t max_data_length = 15;
        static const uint32_t clock_speed = 400000;
    };

    // I2C1 manager configs
    struct I2C1_man
    {
        static const bool release_bus = 0;
        static const uint8_t max_data_length = 15;
        static const uint32_t clock_speed = 400000;
    };

    // Esc controller configs
    struct ESC
    {
        // ESC Controller - escct

        static const uint16_t min_signal = 1000;
        static const uint16_t min_throttle = 100;
        static const uint16_t max_throttle = 900;
        static const uint8_t esc1_pin = 5; // front-right
        static const uint8_t esc2_pin = 2; // rear-right
        static const uint8_t esc3_pin = 3; // rear-left
        static const uint8_t esc4_pin = 4; // front-left

        struct timer
        {
            static const uint64_t begin_time = 3700;
            static const uint64_t end_time = 3720;
            static const uint64_t warning_time = 0;
            static const bool begin_block = 1;
            static const bool end_block = 1;
        };
    };

    // Main and sub timer configs
    struct Timer
    {
        static const bool main_endblock = 1;
        static const uint64_t main_turn_duration = 4000;
        static const uint8_t sub_timsta_arr_len = 5;
    };

    // Debug in and out configs
    struct Dbg
    {
        static const uint64_t serial0_baud_rate = 250000;
        static const uint64_t out_fatal_loop_wait = 100000;
        static const uint32_t out_buffer_length = 2000;
        static const int8_t out_max_precision = 8;
        static const int8_t out_def_precision = 2;
        static const int8_t out_def_round_mode = 2; // 1-floor, 2-round
        static const uint32_t in_buffer_length = 2000;
        static const uint64_t in_parse_waittime = 300;
        static const uint64_t in_read_serial_byte_delay = 150; // 12/250000*1000000=48*3~150
    };

    // RPI Serial configs
    struct Serial
    {
        static const uint64_t serial2_baud_rate = 115200; // 460800
    };
};
#endif // !CONFIG_H