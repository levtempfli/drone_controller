#include "ESCCT.h"

escct::escct() {
	esc1.attach(ESCCT_ESC1PIN);
	esc2.attach(ESCCT_ESC2PIN);
	esc3.attach(ESCCT_ESC3PIN);
	esc4.attach(ESCCT_ESC4PIN);
	stop_motors();
}

void escct::init() {
	delayMicroseconds(ESCCT_INIT_WAIT_TIME);
}

void escct::start_motors(){
	started = true;
	esc1.writeMicroseconds(1000 + ESCCT_MINTHROTTLE);
	esc2.writeMicroseconds(1000 + ESCCT_MINTHROTTLE);
	esc3.writeMicroseconds(1000 + ESCCT_MINTHROTTLE);
	esc4.writeMicroseconds(1000 + ESCCT_MINTHROTTLE);
}

void escct::stop_motors(){
	started = false;
	esc1.writeMicroseconds(1000);
	esc2.writeMicroseconds(1000);
	esc3.writeMicroseconds(1000);
	esc4.writeMicroseconds(1000);
}

void escct::set_throttle(int32_t  t1, int32_t  t2, int32_t  t3, int32_t  t4) {
	timer_s.begin();

	if (started == false) {
		timer_s.end();
		return;
	}

	if (t1 < ESCCT_MINTHROTTLE) esc1.writeMicroseconds(1000 + ESCCT_MINTHROTTLE);
	else if (t1 > ESCCT_MAXTHROTTLE) esc1.writeMicroseconds(1000 + ESCCT_MAXTHROTTLE);
	else esc1.writeMicroseconds(1000 + t1);

	if (t2 < ESCCT_MINTHROTTLE) esc2.writeMicroseconds(1000 + ESCCT_MINTHROTTLE);
	else if (t2 > ESCCT_MAXTHROTTLE) esc2.writeMicroseconds(1000 + ESCCT_MAXTHROTTLE);
	else esc2.writeMicroseconds(1000 + t2);

	if (t3 < ESCCT_MINTHROTTLE) esc3.writeMicroseconds(1000 + ESCCT_MINTHROTTLE);
	else if (t3 > ESCCT_MAXTHROTTLE) esc3.writeMicroseconds(1000 + ESCCT_MAXTHROTTLE);
	else esc3.writeMicroseconds(1000 + t3);

	if (t4 < ESCCT_MINTHROTTLE) esc4.writeMicroseconds(1000 + ESCCT_MINTHROTTLE);
	else if (t4 > ESCCT_MAXTHROTTLE) esc4.writeMicroseconds(1000 + ESCCT_MAXTHROTTLE);
	else esc4.writeMicroseconds(1000 + t4);

	timer_s.end();
	return;
}
