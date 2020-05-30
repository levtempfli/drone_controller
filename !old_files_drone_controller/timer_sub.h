#ifndef TIMER_SUB_H
#define TIMER_SUB_H

#include <stdint.h>
#include <Arduino.h>
#include "timer_main.h"
#include "config.h"

extern timer_main _timer_m;

class timer_sub {
public:
	timer_sub(uint64_t cbt, uint64_t cet, bool cbb, bool ceb, uint64_t cwt);
	void begin();
	bool warning();
	void end();
	void set_new_timestamp(uint8_t i);
	uint64_t get_timestamp(uint8_t i);
	uint64_t get_time_since_timestamp(uint8_t i);
private:
	uint64_t c_begin_time;
	uint64_t c_end_time;
	bool c_begin_block;
	bool c_end_block;
	uint64_t c_warning_time;
	uint64_t timestamps[TIMER_SUB_TS_ARRAYLENGTH + 1];
};

#endif // !TIMER_SUB_H

