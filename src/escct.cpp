#include "escct.h"
#include <Servo.h>

// Constructor
escct::escct(timer_main &tm)
    : timer_s(CFG::ESC::timer::begin_time, CFG::ESC::timer::end_time, CFG::ESC::timer::begin_block,
              CFG::ESC::timer::end_block, CFG::ESC::timer::warning_time, tm),
      timer_m(tm)
{
    esc1.attach(CFG::ESC::esc1_pin);
    esc2.attach(CFG::ESC::esc2_pin);
    esc3.attach(CFG::ESC::esc3_pin);
    esc4.attach(CFG::ESC::esc4_pin);
    stop_motors();
}

// Starts motors on minimum throttle
void escct::start_motors()
{
    started = true;
    esc1.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::min_throttle);
    esc2.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::min_throttle);
    esc3.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::min_throttle);
    esc4.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::min_throttle);
}

// Stops motors
void escct::stop_motors()
{
    started = false;
    esc1.writeMicroseconds(CFG::ESC::min_signal);
    esc2.writeMicroseconds(CFG::ESC::min_signal);
    esc3.writeMicroseconds(CFG::ESC::min_signal);
    esc4.writeMicroseconds(CFG::ESC::min_signal);
}

// Set throttle of individual motors
void escct::set_throttle(int32_t t1, int32_t t2, int32_t t3, int32_t t4)
{
    timer_s.begin();

    if (started == false)
    {
        timer_s.end();
        return;
    }

    if (t1 < CFG::ESC::min_throttle)
        esc1.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::min_throttle);
    else if (t1 > CFG::ESC::max_throttle)
        esc1.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::max_throttle);
    else
        esc1.writeMicroseconds(CFG::ESC::min_signal + t1);

    if (t2 < CFG::ESC::min_throttle)
        esc2.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::min_throttle);
    else if (t2 > CFG::ESC::max_throttle)
        esc2.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::max_throttle);
    else
        esc2.writeMicroseconds(CFG::ESC::min_signal + t2);

    if (t3 < CFG::ESC::min_throttle)
        esc3.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::min_throttle);
    else if (t3 > CFG::ESC::max_throttle)
        esc3.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::max_throttle);
    else
        esc3.writeMicroseconds(CFG::ESC::min_signal + t3);

    if (t4 < CFG::ESC::min_throttle)
        esc4.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::min_throttle);
    else if (t4 > CFG::ESC::max_throttle)
        esc4.writeMicroseconds(CFG::ESC::min_signal + CFG::ESC::max_throttle);
    else
        esc4.writeMicroseconds(CFG::ESC::min_signal + t4);

    timer_s.end();
    return;
}

// Set RPM based on voltage
void escct::set_rpm(double r1, double r2, double r3, double r4, double voltage)
{
    r1=CFG::ESC::lin_reg_theta1+r1*CFG::ESC::lin_reg_theta2+voltage*CFG::ESC::lin_reg_theta3+r1*voltage*CFG::ESC::lin_reg_theta4;
    r2=CFG::ESC::lin_reg_theta1+r2*CFG::ESC::lin_reg_theta2+voltage*CFG::ESC::lin_reg_theta3+r2*voltage*CFG::ESC::lin_reg_theta4;
    r3=CFG::ESC::lin_reg_theta1+r3*CFG::ESC::lin_reg_theta2+voltage*CFG::ESC::lin_reg_theta3+r3*voltage*CFG::ESC::lin_reg_theta4;
    r4=CFG::ESC::lin_reg_theta1+r4*CFG::ESC::lin_reg_theta2+voltage*CFG::ESC::lin_reg_theta3+r4*voltage*CFG::ESC::lin_reg_theta4;
    set_throttle(r1,r2,r3,r4);
}
