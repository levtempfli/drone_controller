#include "ESCCT.h"

escct::escct() {
	esc1.attach(ESCCT_ESC1PIN);
	esc2.attach(ESCCT_ESC2PIN);
	esc3.attach(ESCCT_ESC3PIN);
	esc4.attach(ESCCT_ESC4PIN);
	stop_motors();
}

void escct::start_motors(){
	started = true;
	esc1.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MINTHROTTLE);
	esc2.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MINTHROTTLE);
	esc3.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MINTHROTTLE);
	esc4.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MINTHROTTLE);
}

void escct::stop_motors(){
	started = false;
	esc1.writeMicroseconds(ESCCT_MINSIGNAL);
	esc2.writeMicroseconds(ESCCT_MINSIGNAL);
	esc3.writeMicroseconds(ESCCT_MINSIGNAL);
	esc4.writeMicroseconds(ESCCT_MINSIGNAL);
}

void escct::set_throttle(int32_t  t1, int32_t  t2, int32_t  t3, int32_t  t4) {
	timer_s.begin();

	if (started == false) {
		timer_s.end();
		return;
	}

	if (t1 < ESCCT_MINTHROTTLE) esc1.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MINTHROTTLE);
	else if (t1 > ESCCT_MAXTHROTTLE) esc1.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MAXTHROTTLE);
	else esc1.writeMicroseconds(ESCCT_MINSIGNAL + t1);

	if (t2 < ESCCT_MINTHROTTLE) esc2.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MINTHROTTLE);
	else if (t2 > ESCCT_MAXTHROTTLE) esc2.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MAXTHROTTLE);
	else esc2.writeMicroseconds(ESCCT_MINSIGNAL + t2);

	if (t3 < ESCCT_MINTHROTTLE) esc3.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MINTHROTTLE);
	else if (t3 > ESCCT_MAXTHROTTLE) esc3.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MAXTHROTTLE);
	else esc3.writeMicroseconds(ESCCT_MINSIGNAL + t3);

	if (t4 < ESCCT_MINTHROTTLE) esc4.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MINTHROTTLE);
	else if (t4 > ESCCT_MAXTHROTTLE) esc4.writeMicroseconds(ESCCT_MINSIGNAL + ESCCT_MAXTHROTTLE);
	else esc4.writeMicroseconds(ESCCT_MINSIGNAL + t4);

	timer_s.end();
	return;
}
