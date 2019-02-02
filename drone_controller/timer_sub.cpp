#include "timer_sub.h"

void timer_sub::begin() {
	uint64_t turn_elapsed = _timer_m.get_turn_time();
	if (turn_elapsed > c_begin_time) {
		_timer_m.add_sub_errors(turn_elapsed - c_begin_time);
		return;
	}
	if (c_begin_block == 1) {
		while (_timer_m.get_turn_time() < c_begin_time) {
			delayMicroseconds(1);
		}
	}
	
	return;
}

void timer_sub::end() {
	uint64_t turn_elapsed = _timer_m.get_turn_time();
	if (turn_elapsed > c_end_time) {
		_timer_m.add_sub_errors(turn_elapsed - c_end_time);
		return;
	}
	if (c_end_block == 1) {
		while (_timer_m.get_turn_time() < c_end_time) {
			delayMicroseconds(1);
		}
	}
	return;
}

bool timer_sub::warning() {
	uint64_t turn_elapsed = _timer_m.get_turn_time();
	if (turn_elapsed > c_warning_time) {
		return 1;
	}
	return 0;
}

void timer_sub::set_new_timestamp(uint8_t i) {
	timestamps[i] = _timer_m.get_total_time();
}

uint64_t timer_sub::get_timestamp(uint8_t i) {
	return timestamps[i];
}

uint64_t timer_sub::get_time_since_timestamp(uint8_t i) {
	return _timer_m.get_total_time() - timestamps[i];
}

timer_sub::timer_sub(uint64_t cbt, uint64_t cet, bool cbb, bool ceb, uint64_t cwt) {
	c_begin_time = cbt;
	c_end_time = cet;
	c_begin_block = cbb;
	c_end_block = ceb;
	c_warning_time = cwt;
	for (uint8_t i = 0; i <= TIMER_SUB_TS_ARRAYLENGTH; i++) {
		timestamps[i] = 0;
	}
}