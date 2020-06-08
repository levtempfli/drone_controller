#include "timer_main.h"
#include <Arduino.h>
#undef min
#undef max
// main loop begin measurement
void timer_main::turn_begin()
{
    turn_begin_time = micros();
}

// main loop end measurement
void timer_main::turn_end()
{
    uint64_t turn_elapsed;
    turn_elapsed = micros() - turn_begin_time;
    if (turn_elapsed > CFG::Timer::main_turn_duration)
    {
        main_errors += turn_elapsed - CFG::Timer::main_turn_duration;
        return;
    }
    if (CFG::Timer::main_endblock == 1)
    {
        while (micros() - turn_begin_time < CFG::Timer::main_turn_duration)
        {
            delayMicroseconds(1);
        }
    }
    return;
}

// get time elapsed from begin
uint64_t timer_main::get_total_time() const
{
    return micros();
}

// get time elapsed from start
uint64_t timer_main::get_turn_time() const
{
    return micros() - turn_begin_time;
}

// get main time delays
uint64_t timer_main::get_main_errors() const
{
    return main_errors;
}

// get sub begin time delays
uint64_t timer_main::get_sub_begin_errors() const
{
    return sub_begin_errors;
}

// get sub end time delays
uint64_t timer_main::get_sub_end_errors() const
{
    return sub_end_errors;
}

// get sub begin+end delay
uint64_t timer_main::get_sub_errors() const
{
    return sub_begin_errors + sub_end_errors;
}

// add to sub begin errors
void timer_main::add_sub_begin_errors(uint64_t dt)
{
    sub_begin_errors += dt;
}

// add to sub end errors
void timer_main::add_sub_end_errors(uint64_t dt)
{
    sub_end_errors += dt;
}
