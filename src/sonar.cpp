#include "sonar.h"

sonar::sonar(timer_main &tm)
    : timer_s(CFG::Sonar::timer::begin_time, CFG::Sonar::timer::end_time, CFG::Sonar::timer::begin_block,
              CFG::Sonar::timer::end_block, CFG::Sonar::timer::warning_time, tm),
      timer_m(tm)
{
}

void sonar::init()
{
    pinMode(CFG::Sonar::trigger_pin, OUTPUT); // Sets the trigPin as an Output
    pinMode(CFG::Sonar::echo_pin, INPUT);     // Sets the echoPin as an Input
    duration = 0;
    distance = 0;
    timer_s.set_new_timestamp(0);
    on_the_ground = 0;
}

void sonar::start_sound()
{
    digitalWrite(CFG::Sonar::trigger_pin, LOW); // Clears the trigPin
    delayMicroseconds(CFG::Sonar::digital_delay);
    digitalWrite(CFG::Sonar::trigger_pin, HIGH); // Sets the trigPin on HIGH state for 10 micro seconds
    delayMicroseconds(CFG::Sonar::digital_delay);
    digitalWrite(CFG::Sonar::trigger_pin, LOW);
    timer_s.set_new_timestamp(1);
}

void sonar::measure()
{
    timer_s.begin();

    int64_t wait_for_signal_timeout = CFG::Sonar::timer::warning_time - timer_m.get_turn_time();

    if (wait_for_signal_timeout > 0)
        duration = pulseIn(CFG::Sonar::echo_pin, HIGH, wait_for_signal_timeout);
    else
        duration = 0;

    distance = duration * CFG::Sonar::sound_distance_in_1ms / 2; // Calculating the distance

    if (distance < CFG::Sonar::max_distance_from_ground && distance != 0)
    {
        timer_s.set_new_timestamp(0);
        on_the_ground = 1;
    }
    if (timer_s.get_time_since_timestamp(0) > CFG::Sonar::data_timeout)
    {
        on_the_ground = 0;
    }

    timer_s.end();
}

bool sonar::is_it_on_the_ground()
{
    return on_the_ground;
}
