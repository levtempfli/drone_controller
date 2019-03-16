#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <stdint.h>
#include "timer_sub.h"

class battery_monitor {
public:
	double get_current();
	double get_voltage();
	int32_t get_motor_correction();
	void init();
	void update();
	double get_percentage();
	int32_t get_remaining_time();
	
private:
	timer_sub timer_s = timer_sub(BTM_TIMER_BEGINTIME, BTM_TIMER_ENDTIME, BTM_TIMER_BEGINBLOCK, BTM_TIMER_ENDBLOCK, BTM_TIMER_WARNINGTIME);
	double voltage, current, voltage_avg, current_avg, percentage;
	int32_t motor_compensation, remaining_time;
};

#endif // !BATTERY_MONITOR_H
