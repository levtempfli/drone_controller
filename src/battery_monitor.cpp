#include "battery_monitor.h"

battery_monitor::battery_monitor(timer_main &tm)
    : timer_s(CFG::battery_monitor::timer::begin_time, CFG::battery_monitor::timer::end_time,
              CFG::battery_monitor::timer::begin_block, CFG::battery_monitor::timer::end_block,
              CFG::battery_monitor::timer::warning_time, tm),
      timer_m(tm)
{
}

void battery_monitor::update()
{
    timer_s.begin();

    voltage = analogRead(CFG::battery_monitor::voltage::sensor_pin);
    current = analogRead(CFG::battery_monitor::current::sensor_pin);
    voltage = voltage * CFG::battery_monitor::sensor_voltage / CFG::battery_monitor::sensor_res;
    // voltage *= CFG::battery_monitor::voltage::conv_val;
    voltage = CFG::battery_monitor::voltage::lin_reg_theta2 * voltage + CFG::battery_monitor::voltage::lin_reg_theta1;
    current = current * CFG::battery_monitor::sensor_voltage / CFG::battery_monitor::sensor_res;
    current *= CFG::battery_monitor::current::conv_val;
    voltage_avg = voltage_avg * CFG::battery_monitor::voltage::compl_filter_alpha +
                  voltage * CFG::battery_monitor::voltage::compl_filter_1malpha;
    current_avg = current_avg * CFG::battery_monitor::voltage::compl_filter_alpha +
                  current * CFG::battery_monitor::voltage::compl_filter_1malpha;

    percentage = (voltage_avg - CFG::battery_monitor::bat_0per_vlt) /
                 (CFG::battery_monitor::bat_100per_vlt - CFG::battery_monitor::bat_0per_vlt);
    remaining_time = 60 * (CFG::battery_monitor::bat_mah * percentage) / (current_avg * 1000);
    percentage *= 100;

    timer_s.end();
}

double battery_monitor::get_current()
{
    return current_avg;
}

double battery_monitor::get_voltage()
{
    return voltage_avg;
}

void battery_monitor::init()
{
    voltage = analogRead(CFG::battery_monitor::voltage::sensor_pin);
    current = analogRead(CFG::battery_monitor::current::sensor_pin);
    voltage = voltage * CFG::battery_monitor::sensor_voltage / CFG::battery_monitor::sensor_res;
    // voltage *= CFG::battery_monitor::voltage::conv_val;
    voltage = CFG::battery_monitor::voltage::lin_reg_theta2 * voltage + CFG::battery_monitor::voltage::lin_reg_theta1;
    current = current * CFG::battery_monitor::sensor_voltage / CFG::battery_monitor::sensor_res;
    current *= CFG::battery_monitor::current::conv_val;
    voltage_avg = voltage;
    current_avg = current;
}

double battery_monitor::get_percentage()
{
    return percentage;
}

int32_t battery_monitor::get_remaining_time()
{
    return remaining_time;
}
