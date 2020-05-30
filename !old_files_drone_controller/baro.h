#ifndef BARO_H
#define BARO_H

#include <stdint.h>
#include "timer_sub.h"
#include "I2C1_manager.h"
#include "debug_in.h"
#include "debug_out.h"

extern i2c1_manager _i2c1_mng;
extern debug_in din;
extern debug_out dout;

class baro {
public:
	
	void init();
	void set_altitude(double altitude);
	void update();
	double get_pressure(uint8_t mode = 1);
	double get_temperature();
	double get_altitude();
	bool is_there_new_pressure();

private:
	timer_sub timer_s = timer_sub(BARO_TIMER_BEGINTIME, BARO_TIMER_ENDTIME, BARO_TIMER_BEGINBLOCK, BARO_TIMER_ENDBLOCK, BARO_TIMER_WARNINGTIME);
	int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
	uint16_t ac4, ac5, ac6;
	uint8_t oversampling;
	int32_t UT, B5;
	int32_t pressure;
	int32_t sealevelpressure;
	int32_t rot_mem[BARO_NUM_OF_AVG];
	int16_t rot_mem_i;
	int32_t rot_sum;
	double rot_avg;
	double compl_1_corr, compl_2;
	bool curr_measurement;//0-temperature 1-pressure
	bool new_pressure_data;
	double altitude;
	double temp;
	void start_temp();
	void start_press();
	void read_temp();
	void read_press();
	void calc_altitude();
};



#endif // !BARO_H
