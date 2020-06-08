#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

// Configurations
struct CFG
{
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