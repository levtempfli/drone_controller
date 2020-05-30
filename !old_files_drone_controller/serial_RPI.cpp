#include "serial_RPI.h"

void ser_rpi::init() {
	Serial2.begin(SER_SERIAL2_BAUD_RATE);
	Serial2.setTimeout(0);
}

void ser_rpi::init_fast() {
	timer_s.set_new_timestamp(1);//conn_msg_timer
	timer_s.set_new_timestamp(2);//msg_send_timer
}

void ser_rpi::update() {
	timer_s.begin();
	uint32_t rec;

	rec = Serial2.available();
	if (rec > 0) {
		rec = Serial2.readBytes(in_buffer, SER_INBUFF_SIZE);
		if (rec > 0) {
			decode_message(rec);
			timer_s.set_new_timestamp(1);//conn_msg_timer
		}
	}


	uint32_t sent, to_st = encode_message();
	if (to_st != 0) {
		sent = Serial2.write(out_buffer, to_st);
		if (to_st == sent) {
			timer_s.set_new_timestamp(2);//msg_send_timer
			msg_types_curr++;
			if (msg_types_curr > SER_MSG_TYPES_MAX) msg_types_curr = 1;
		}
	}

	if (timer_s.get_time_since_timestamp(1) > SER_CONN_MSG_TIMEOUT) {
		serial_ack = 0;
	}
	else if (serial_ack == 0) {
		serial_ack = 1;
	}
	timer_s.end();
}

void ser_rpi::decode_message(uint32_t rec) {
	char char_rec;
	for (uint32_t i = 0; i < rec; i++) {
		char_rec = in_buffer[i];
		switch (char_rec) {
		case '@':
			in_status = 1;
			slv_buff_i = 0;
			break;
		case '~':
			if (in_status != 1) break;
			in_status = 2;
			break;
		default:
			switch (in_status) {
			case 1:
				if (slv_buff_i == SER_SLVBUFF_SIZE - 1) {
					in_status = 0;
					break;
				}
				slv_buff_i++;
				slv_buffer[slv_buff_i] = char_rec;
				break;
			case 2:
				if (char_rec < 58) in_chd_1 = char_rec - 48;
				else in_chd_1 = char_rec - 55;
				in_status = 3;
				break;
			case 3:
				if (char_rec < 58) in_chd_2 = char_rec - 48;
				else in_chd_2 = char_rec - 55;
				in_chd_1 = in_chd_1 * 16 + in_chd_2;
				if (in_chd_1 == calculate_checksum(slv_buffer, 1, slv_buff_i)) solve_message(slv_buff_i, 1);
				else solve_message(slv_buff_i, 0);
				in_status = 0;
				break;
			}
			break;
		}
	}
}


uint32_t ser_rpi::encode_message() {
	if (timer_s.get_time_since_timestamp(2) > SER_SEND_PERIOD) {
		uint32_t len = create_message(msg_types_curr);
		out_buffer[0] = '@';
		uint8_t chs = calculate_checksum(out_buffer, 1, len);
		len++;
		out_buffer[len] = '~';
		len++;
		if (chs / 16 < 10) out_buffer[len] = 48 + (chs / 16);
		else out_buffer[len] = (chs / 16) - 10 + 65;
		len++;
		if (chs % 16 < 10) out_buffer[len] = 48 + (chs % 16);
		else out_buffer[len] = (chs % 16) - 10 + 65;
		return len + 1;
	}
	else return 0;
}

void ser_rpi::solve_message(uint32_t len, bool correct) {
	Serial.print(correct);
	for (uint32_t i = 1; i <= len; i++) {
		Serial.write(slv_buffer[i]);
	}
}

uint32_t ser_rpi::create_message(uint8_t type) {
	switch (type) {
	case 1:
		strcpy(out_buffer, "Rhello1Z");
		return 7;
		break;
	case 2:
		strcpy(out_buffer, "Rhello2Z");
		return 7;
		break;
	case 3:
		strcpy(out_buffer, "Rhello3Z");
		return 7;
		break;
	default:
		return 0;
		break;
	}
}

uint8_t ser_rpi::calculate_checksum(char * buff, uint32_t begin, uint32_t end) {
	int chs = 0;
	for (int i = begin; i <= end; i++) {
		chs = chs ^ buff[i];
	}
	return chs;
}