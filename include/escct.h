#ifndef ESCCT_H
#define ESCCT_H
#include "config.h"
#include "timer_sub.h"
#include <Servo.h>
#include <stdint.h>

// ESC control class
class escct
{
  public:
    void set_throttle(int32_t t1, int32_t t2, int32_t t3, int32_t t4); // Set throttle of individual motors
    void start_motors();                                               // Starts motors on minimum throttle
    void stop_motors();                                                // Stops motors
    escct(timer_main &tm);                                             // Constructor
    escct() = delete;
    escct(const escct &) = delete;

  private:
    Servo esc1, esc2, esc3, esc4;
    bool started;
    timer_sub timer_s;
};

#endif // !ESCCT_H
