#ifndef TIMER_MAIN_H
#define TIMER_MAIN_H

#include "config.h"
#include <stdint.h>

// Main timer class
class timer_main
{
  public:
    void turn_begin();                      // main loop begin measurement
    void turn_end();                        // main loop end measurement
    uint64_t get_turn_time() const;         // get time elapsed from begin
    uint64_t get_total_time() const;        // get time elapsed from start
    uint64_t get_main_errors() const;       // get main time delays
    uint64_t get_sub_begin_errors() const;  // get sub begin time delays
    uint64_t get_sub_end_errors() const;    // get sub end time delays
    uint64_t get_sub_errors() const;        // get sub begin+end delay
    void add_sub_begin_errors(uint64_t dt); // add to sub begin errors
    void add_sub_end_errors(uint64_t dt);   // add to sub end errors
  private:
    uint64_t main_errors = 0;
    uint64_t sub_begin_errors = 0;
    uint64_t sub_end_errors = 0;
    uint64_t turn_begin_time = 0;
};

#endif // !TIMER_MAIN_H
