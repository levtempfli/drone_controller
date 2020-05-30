#include "battery_monitor.h"

void battery_monitor::update() {
	timer_s.begin();
	

	voltage = analogRead(BTM_VLT_SENSOR_PIN);
	current = analogRead(BTM_CUR_SENSOR_PIN);
	voltage = voltage * BTM_SENSOR_VOLTAGE / BTM_SENSOR_RESOLUTION;
	voltage *= BTM_VLT_CONV_VAL;
	current = current * BTM_SENSOR_VOLTAGE / BTM_SENSOR_RESOLUTION;
	current *= BTM_CUR_CONV_VAL;
	voltage_avg = voltage_avg * BTM_VLT_COMPL_FILTER_ALFA + voltage * BTM_VLT_COMPL_FILTER_1MALFA;
	current_avg = current_avg * BTM_CUR_COMPL_FILTER_ALFA + current * BTM_CUR_COMPL_FILTER_1MALFA;

	percentage = (voltage_avg - BTM_BAT_0PER_VLT) / (BTM_BAT_100PER_VLT - BTM_BAT_0PER_VLT);
	remaining_time = 60 * (BTM_BAT_MAH*percentage) / (current_avg * 1000);
	percentage *= 100;

	//thr +=(float) thr*(12.40 - accumulator) /5;
	//thr = thr * (12.60 / accumulator);
	motor_compensation = (BTM_COMP_REF_VLT - voltage_avg) * BTM_COMP_VAL;
	
	timer_s.end();
}

double battery_monitor::get_current() {
	return current_avg;
}

double battery_monitor::get_voltage() {
	return voltage_avg;
}

int32_t battery_monitor::get_motor_correction() {
	return motor_compensation;
}

void battery_monitor::init() {
	voltage = analogRead(BTM_VLT_SENSOR_PIN);
	current = analogRead(BTM_CUR_SENSOR_PIN);
	voltage = voltage * BTM_SENSOR_VOLTAGE / BTM_SENSOR_RESOLUTION;
	voltage *= BTM_VLT_CONV_VAL;
	current = current * BTM_SENSOR_VOLTAGE / BTM_SENSOR_RESOLUTION;
	current *= BTM_CUR_CONV_VAL;
	voltage_avg = voltage;
	current_avg = current;
}

double battery_monitor::get_percentage() {
	return percentage;
}

int32_t battery_monitor::get_remaining_time() {
	return remaining_time;
}
