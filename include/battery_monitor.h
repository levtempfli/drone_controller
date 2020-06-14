#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include "timer_sub.h"
#include <stdint.h>

class battery_monitor
{
  public:
    battery_monitor() = delete;
    battery_monitor(const battery_monitor &) = delete;
    battery_monitor(timer_main &tm);
    double get_current();
    double get_voltage();
    void init();
    void update();
    double get_percentage();
    int32_t get_remaining_time();

  private:
    timer_sub timer_s;
    timer_main &timer_m;
    double voltage, current, voltage_avg, current_avg, percentage;
    int32_t remaining_time;
};

#endif // !BATTERY_MONITOR_H
