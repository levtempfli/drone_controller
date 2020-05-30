#ifndef SONAR_H
#define SONAR_H

#include "timer_sub.h"


class sonar {
public:
	void init();
	void update();
	bool is_it_on_the_ground();
private:
	timer_sub timer_s = timer_sub(SONAR_TIMER_BEGINTIME, SONAR_TIMER_ENDTIME, SONAR_TIMER_BEGINBLOCK, SONAR_TIMER_ENDBLOCK, SONAR_TIMER_WARNINGTIME);
	uint32_t duration;
	double distance;
	bool on_the_ground;
};

#endif // !SONAR_H

