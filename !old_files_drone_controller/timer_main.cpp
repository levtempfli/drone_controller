#include "timer_main.h"

void timer_main::turn_begin() {
	turn_begin_time = micros();
}

void timer_main::turn_end() {
	uint64_t turn_elapsed;
	turn_elapsed = micros() - turn_begin_time;
	if (turn_elapsed > TIMER_MAIN_TURNTOTAL) {
		main_errors += turn_elapsed - TIMER_MAIN_TURNTOTAL;
		return;
	}
	if (TIMER_MAIN_ENDBLOCK == 1) {
		while (micros() - turn_begin_time < TIMER_MAIN_TURNTOTAL) {
			delayMicroseconds(1);
		}
	}
	return;
}

uint64_t timer_main::get_total_time() {
	total_time = micros();
	return total_time;
}

uint64_t timer_main::get_turn_time() {
	return micros() - turn_begin_time;
}

uint64_t timer_main::get_main_errors() {
	return main_errors;
}

uint64_t timer_main::get_sub_begin_errors() {
	return sub_begin_errors;
}

uint64_t timer_main::get_sub_end_errors() {
	return sub_end_errors;
}

uint64_t timer_main::get_sub_errors() {
	return sub_begin_errors + sub_end_errors;
}

void timer_main::add_sub_begin_errors(uint64_t dt){
	sub_begin_errors += dt;
}

void timer_main::add_sub_end_errors(uint64_t dt) {
	sub_end_errors += dt;
}
