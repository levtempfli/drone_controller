#include "timer_sub.h"

// begin sub-turn
void timer_sub::begin()
{
    uint64_t turn_elapsed = tim_ma.get_turn_time();
    if (turn_elapsed > c_begin_time)
    {
        tim_ma.add_sub_begin_errors(turn_elapsed - c_begin_time);
        return;
    }
    if (c_begin_block == 1)
    {
        while (tim_ma.get_turn_time() < c_begin_time)
        {
            delayMicroseconds(1);
        }
    }

    return;
}

// end sub-turn
void timer_sub::end()
{
    uint64_t turn_elapsed = tim_ma.get_turn_time();
    if (turn_elapsed > c_end_time)
    {
        tim_ma.add_sub_end_errors(turn_elapsed - c_end_time);
        return;
    }
    if (c_end_block == 1)
    {
        while (tim_ma.get_turn_time() < c_end_time)
        {
            delayMicroseconds(1);
        }
    }
    return;
}

// warning check
bool timer_sub::warning() const
{
    uint64_t turn_elapsed = tim_ma.get_turn_time();
    if (turn_elapsed > c_warning_time)
    {
        return 1;
    }
    return 0;
}

// set timestamp i
void timer_sub::set_new_timestamp(uint8_t i)
{
    timestamps[i] = tim_ma.get_total_time();
}

// get timestamp i
uint64_t timer_sub::get_timestamp(uint8_t i) const
{
    return timestamps[i];
}

// get time elapsed since last timestamp set
uint64_t timer_sub::get_time_since_timestamp(uint8_t i) const
{
    return tim_ma.get_total_time() - timestamps[i];
}

// constructor=begin time, end time, beginblock, endblock, warning time
timer_sub::timer_sub(uint64_t cbt, uint64_t cet, bool cbb, bool ceb, uint64_t cwt, timer_main &tm) : tim_ma(tm)
{
    c_begin_time = cbt;
    c_end_time = cet;
    c_begin_block = cbb;
    c_end_block = ceb;
    c_warning_time = cwt;
    for (uint8_t i = 0; i <= CFG::Timer::sub_timsta_arr_len; i++)
    {
        timestamps[i] = 0;
    }
}