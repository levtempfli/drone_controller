#ifndef ESCCT_H
#define ESCCT_H
#include <Servo.h>
#include <stdint.h>
#include "config.h"
#include "timer_sub.h"


class escct {
public:
	void set_throttle(int32_t t1, int32_t  t2, int32_t  t3, int32_t  t4);
	escct();
	void start_motors();
	void stop_motors();
private:
	Servo esc1, esc2, esc3, esc4;
	bool started;
	timer_sub timer_s = timer_sub(ESCCT_TIMER_BEGINTIME, ESCCT_TIMER_ENDTIME, ESCCT_TIMER_BEGINBLOCK, ESCCT_TIMER_ENDBLOCK, ESCCT_TIMER_WARNINGTIME);
};

#endif // !ESCCT_H
