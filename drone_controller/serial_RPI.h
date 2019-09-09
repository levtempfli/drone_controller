#ifndef SERIALRPI_H
#define SERIALRPI_H

#include "timer_sub.h"
#include "debug_in.h"
#include "debug_out.h"

extern debug_out dout;
extern debug_in din;

class ser_rpi {
public:
	void init();
	void init_fast();
	void update();
private:
	timer_sub timer_s = timer_sub(SER_TIMER_BEGINTIME, SER_TIMER_ENDTIME, SER_TIMER_BEGINBLOCK, SER_TIMER_ENDBLOCK, SER_TIMER_WARNINGTIME);
	//timestamp 1-conn_msg_timer, 2-msg_send_timer
	uint8_t msg_types_curr = 1;
	bool serial_ack = 0;
	uint8_t in_status;
	uint8_t in_chd_1;
	uint8_t in_chd_2;
	uint32_t slv_buff_i;
	char in_buffer[SER_INBUFF_SIZE];
	char out_buffer[SER_OUTBUFF_SIZE];
	char slv_buffer[SER_SLVBUFF_SIZE];
	void decode_message(uint32_t rec);
	uint32_t encode_message();
	void solve_message(uint32_t len, bool correct);
	uint32_t create_message(uint8_t type);
	uint8_t calculate_checksum(char *buff, uint32_t begin, uint32_t end);
};

#endif // !SERIALRPI_H

