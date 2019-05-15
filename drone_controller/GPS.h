#ifndef GPS_H
#define GPS_H

#include <stdint.h>
#include <Arduino.h>
#include <math.h>
#include "timer_sub.h"

class GPS {
public:
	void init();
	void update();

	uint8_t get_navMode();
	double get_PDOP();
	int32_t get_lat();
	int32_t get_lon();
	int32_t get_lat_est();
	int32_t get_lon_est();
	bool get_status();
	uint8_t get_numSV();
	double get_alt();
	double get_kph();
private:
	timer_sub timer_s = timer_sub(GPS_TIMER_BEGINTIME, GPS_TIMER_ENDTIME, GPS_TIMER_BEGINBLOCK, GPS_TIMER_ENDBLOCK, GPS_TIMER_WARNINGTIME);
	
	uint8_t navMode;//0-no fix, 2-2Dfix, 3-3Dfix
	double PDOP;//1.53
	double lat_db, lon_db, alt, kph;//47.79671700, 22.88944300, 138.0,0.217
	int32_t lat, lon;//477967170, 228894430
	int32_t lat_prev, lon_prev, lat_est, lon_est;
	double lat_speed, lon_speed;
	uint64_t elapsed;
	bool status;//0/1
	uint8_t numSV;//11
	char NS, EW;//N, E

	int8_t byte_rec;
	uint8_t in_status;//0-wait for $; 1-wair for data; 2-wait for checksum1; 3-wait for checksum2
	int8_t buffer[GPS_BUFF_SIZE];
	uint8_t buff_i;
	uint8_t res_i;
	int8_t chsu, chs1, chs2;

	void field_skip();
	uint16_t field_get_uint16();
	double field_get_double();
	char field_get_char();
	void decode_NMEA();
};

#endif // !GPS_H
