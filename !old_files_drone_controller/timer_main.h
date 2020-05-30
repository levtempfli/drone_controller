#ifndef TIMER_MAIN_H
#define TIMER_MAIN_H

#include <stdint.h>
#include <Arduino.h>
#include "config.h"

class timer_main {
public:
	void turn_begin();
	void turn_end();
	uint64_t get_turn_time();
	uint64_t get_total_time();
	uint64_t get_main_errors();
	uint64_t get_sub_begin_errors();
	uint64_t get_sub_end_errors();
	uint64_t get_sub_errors();
	void add_sub_begin_errors(uint64_t dt);
	void add_sub_end_errors(uint64_t dt);
private:
	uint64_t main_errors;
	uint64_t sub_begin_errors;
	uint64_t sub_end_errors;
	uint64_t total_time;
	uint64_t turn_begin_time;
};

#endif // !TIMER_MAIN_H

