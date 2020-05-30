#ifndef DEBUG_IN
#define DEBUG_IN
#include "config.h"
#include <Arduino.h>

class debug_in {
public:
	debug_in& operator>>(int &i);
	debug_in& operator>>(int8_t &i);
	debug_in& operator>>(int16_t &i);
	debug_in& operator>>(int32_t &i);
	debug_in& operator>>(int64_t &i);
	debug_in& operator>>(uint8_t &i);
	debug_in& operator>>(uint16_t &i);
	debug_in& operator>>(uint32_t &i);
	debug_in& operator>>(uint64_t &i);
	debug_in& operator>>(double &i);
	debug_in& operator>>(float &i);
	debug_in& operator>>(String &s);
	debug_in& operator>>(char &c);
	void in_write_char(char c);
	bool read_available();
	void getline(String &s);

private:
	void read_from_serial();
	char in_read_char();
	bool in_read_available();
	char in_buffer[DBG_IN_BUFFER_LENGTH];//write from RPI, read from program
	uint32_t in_write_idx = 0;
	uint32_t in_read_idx = 0;


};

#endif // !DEBUG_IN
