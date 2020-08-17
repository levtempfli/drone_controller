#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>
#undef min
#undef max
#include <stdint.h>

// Configurations
struct CFG
{
    static const uint64_t pre_init_delay = 1500000;
    struct GPS
    {
        static const uint16_t buffer_size = 128;
        static const uint32_t def_serial1_baud = 9600;
        static const uint32_t set_serial1_baud = 460800;
        static const uint64_t timeout = 400000;

        struct settings
        {
            static const uint64_t delay = 200000;
            static const uint16_t set_baud_msg_len = 28;
            static const uint8_t set_baud_msg[];
            static const uint16_t denmea_msg_len = 11;
            static const uint8_t disable_GGA[];
            static const uint8_t disable_GLL[];
            static const uint8_t disable_GSV[];
            static const uint8_t disable_TXT[];
            static const uint8_t disable_RMC[];
            static const uint8_t enable_VTG[];
            static const uint8_t enable_GNS[];
            static const uint8_t enable_GSA[];
            static const uint16_t set_rate_msg_len = 14;
            static const uint8_t set_rate_msg[];
        };

        struct timer
        {
            static const uint64_t begin_time = 2000;
            static const uint64_t end_time = 2550;
            static const uint64_t warning_time = 2500;
            static const bool begin_block = 1;
            static const bool end_block = 0;
        };
    };

    struct battery_monitor
    {
        static constexpr double sensor_voltage = 3.3;
        static constexpr double sensor_res = 1024;
        static constexpr double bat_100per_vlt = 12.60;
        static constexpr double bat_0per_vlt = 10.5;
        static const uint16_t bat_mah = 10000;

        struct voltage
        {
            static const uint16_t sensor_pin = A3;
            // static constexpr double conv_val = 10.210;
            static constexpr double lin_reg_theta1 = 1.119101; // 1.alt: 1.119101
            static constexpr double lin_reg_theta2 = 9.288398; // 1.alt: 9.288398
            static constexpr double compl_filter_alpha = 0.95;
            static constexpr double compl_filter_1malpha = 0.05;
        };

        struct current
        {
            static const uint16_t sensor_pin = A2;
            static constexpr double conv_val = 27.3322;
            static constexpr double compl_filter_alpha = 0.95;
            static constexpr double compl_filter_1malpha = 0.05;
        };

        struct timer
        {
            static const uint64_t begin_time = 4150;
            static const uint64_t end_time = 4400;
            static const uint64_t warning_time = 0;
            static const bool begin_block = 1;
            static const bool end_block = 0;
        };
    };

    // Inertial Measurement Unit configs
    struct IMU
    {
        static const uint64_t init_delays = 100000;
        static constexpr double yaw_fusion_alpha = 0.98;
        static constexpr double yaw_fusion_1malpha = 0.02;

        // accelerometer/gyro configs
        struct accgyro
        {
            static const uint8_t I2C_address = 0x68;
            static const uint8_t who_am_i_reg = 0x75;
            static const uint8_t settings_n = 4;
            static const uint8_t settings_reg_addr[];      // defined in config.cpp
            static const uint8_t settings_reg_val[];       // defined in config.cpp
            static const uint8_t read_raw_reg_addr = 0x3B; // 14 values are read
            static constexpr double compl_filter_alpha = 0.98;
            static constexpr double compl_filter_1malpha = 0.02;
            static constexpr double dampen_ang_alpha = 0.9;
            static constexpr double dampen_ang_1malpha = 0.1;

            struct gyro
            {
                static const bool offset_calc = 1;
                static const uint16_t offset_calc_sample_n = 2000;
                static const uint64_t offset_delay = 500;
                static constexpr double def_offset_x = -91.92;
                static constexpr double def_offset_y = -62.97;
                static constexpr double def_offset_z = -48.52;
                static constexpr double sensitivity_scale = 65.5; // uint8_t
            };

            struct acc
            {
                static const int16_t offset_x = 279;
                static const int16_t offset_y = -70;
            };
        };

        // magnetometer configs
        struct magneto
        {
            static const uint8_t I2C_address = 0x1E;
            static const uint8_t ident_start_addr = 0X0A; // 3 registers are read
            static const int32_t ident_val = 4731955;
            static const uint8_t settings_n = 3;
            static const uint8_t settings_reg_addr[]; // defined in config.cpp
            static const uint8_t settings_reg_val[];  // defined in config.cpp
            static constexpr double offset_x = -126;
            static constexpr double offset_y = -0.5;
            static constexpr double offset_z = 128;
            static constexpr double scale_x = 1.068181818;
            static constexpr double scale_y = 0.887947883;
            static constexpr double scale_z = 1.066510172;
            static const uint8_t read_raw_reg_addr = 0x03; // 6 values are read
        };

        // critical timing configs
        struct timer
        {
            static const uint64_t begin_time = 2450;
            static const uint64_t end_time = 3800;
            static const uint64_t warning_time = 0;
            static const bool begin_block = 1;
            static const bool end_block = 0;
        };

        // messages, defined in config.cpp
        struct msg
        {
            static const char acgy_init_error[];
            static const char magn_init_error[];
            static const char gyro_offs_cal_result[];
        };
    };

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
        static constexpr double lin_reg_theta1 = -330.102823;
        static constexpr double lin_reg_theta2 = 0.135228;
        static constexpr double lin_reg_theta3 = 5.755197;
        static constexpr double lin_reg_theta4 = -0.005286;

        // critical timing configs
        struct timer
        {
            static const uint64_t begin_time = 4425;
            static const uint64_t end_time = 4450;
            static const uint64_t warning_time = 0;
            static const bool begin_block = 1;
            static const bool end_block = 0;
        };
    };

    // Main and sub timer configs
    struct Timer
    {
        static const bool main_endblock = 1;
        static const uint64_t main_turn_duration = 4500;
        static const uint8_t sub_timsta_arr_len = 5;
    };

    // RPI Serial configs
    struct Serial
    {
        static const uint64_t serial2_baud_rate = 115200; // 460800
    };

    // Debug in and out configs
    struct Dbg
    {
        static const uint64_t serial0_baud_rate = 115200;
        static const uint64_t out_fatal_loop_wait = 100000;
        static const uint32_t out_buffer_length = 2000;
        static const int8_t out_max_precision = 8;
        static const int8_t out_def_precision = 2;
        static const int8_t out_def_round_mode = 2; // 1-floor, 2-round
        static const uint32_t in_buffer_length = 2000;
        static const uint64_t in_parse_waittime = 300;
        static const uint64_t in_read_serial_byte_delay = 150; // 12/250000*1000000=48*3~150
    };
};
#endif // !CONFIG_H