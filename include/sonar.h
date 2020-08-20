#ifndef SONAR_H
#define SONAR_H

#include "timer_sub.h"

class sonar
{
  public:
    sonar() = delete;
    sonar(const sonar &) = delete;
    sonar(timer_main &tm);
    void init();
    void start_sound();
    void measure();
    bool is_it_on_the_ground();

  private:
    timer_sub timer_s;
    timer_main &timer_m;
    uint32_t duration;
    double distance;
    bool on_the_ground;
};

#endif // !SONAR_H
