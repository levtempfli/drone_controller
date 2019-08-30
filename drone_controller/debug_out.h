#ifndef DEBUG_OUT
#define DEBUG_OUT
#include "config.h"

class debug_out {
public:
	debug_out();
	debug_out& operator<<(int i);
	debug_out& operator<<(int8_t i);
	debug_out& operator<<(int16_t i);
	debug_out& operator<<(int32_t i);
	debug_out& operator<<(int64_t i);
	debug_out& operator<<(uint8_t i);
	debug_out& operator<<(uint16_t i);
	debug_out& operator<<(uint32_t i);
	debug_out& operator<<(uint64_t i);
	debug_out& operator<<(double i);
	debug_out& operator<<(float i);
	debug_out& operator<<(String s);
	debug_out& operator<<(char c);
	void set_precision(int8_t pr);
	void set_round_mode(int8_t m);
	void fatal_error(String s);
	char out_read_char();
	bool out_read_available();
	
private:
	void out_write_char(char c);
	char out_buffer[DBG_OUT_BUFFER_LENGTH];//write from program, read from RPI com
	uint32_t out_write_idx = 0;
	uint32_t out_read_idx = 0;
	int8_t precision = DBG_OUT_DEF_PRECISION;
	int8_t round_mode = DBG_OUT_DEF_ROUND_MODE;


};

#endif // !DEBUG_OUT
