#ifndef TIMER_SUB_H
#define TIMER_SUB_H

#include <Arduino.h>
#include <stdint.h>
#undef min
#undef max
#include "config.h"
#include "timer_main.h"

// Sub timer class
class timer_sub
{
  public:
    timer_sub(uint64_t cbt, uint64_t cet, bool cbb, bool ceb, uint64_t cwt,
              timer_main &tm);               // constructor=begin time, end time, beginblock, endblock, warning time
    void begin();                            // begin sub-turn
    bool warning() const;                    // warning check
    void end();                              // end sub-turn
    void set_new_timestamp(uint8_t i);       // set timestamp i
    uint64_t get_timestamp(uint8_t i) const; // get timestamp i
    uint64_t get_time_since_timestamp(uint8_t i) const; // get time elapsed since last timestamp set
  private:
    timer_main &tim_ma;
    uint64_t c_begin_time;
    uint64_t c_end_time;
    bool c_begin_block;
    bool c_end_block;
    uint64_t c_warning_time;
    uint64_t timestamps[CFG::Timer::sub_timsta_arr_len + 1];
};

#endif // !TIMER_SUB_H
