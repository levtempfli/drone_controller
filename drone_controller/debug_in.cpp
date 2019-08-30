#include "debug_in.h"

debug_in& debug_in::operator>>(int &i) {
	*this >> (int64_t&)i;
	return *this;
}
debug_in& debug_in::operator>>(int8_t &i) {
	*this >> (int64_t&)i;
	return *this;
}
debug_in& debug_in::operator>>(int16_t &i) {
	*this >> (int64_t&)i;
	return *this;
}
debug_in& debug_in::operator>>(int32_t &i) {
	*this >> (int64_t&)i;
	return *this;
}
debug_in& debug_in::operator>>(int64_t &i) {
	read_from_serial();
	i = 0;
	char read_char;
	do {
		if (!in_read_available()) return *this;
		read_char = in_read_char();
		if ((read_char >= 0 && read_char <= 32) || read_char == 127) continue;
		else break;
	} while (1);
	bool negative = 0, digit_detect = 0;
	if (read_char == '-') negative = 1;
	else if (read_char == '+') negative = 0;
	else if (read_char >= '0' && read_char <= '9') digit_detect = 1;
	else return *this;
	if (!digit_detect) {
		if (in_read_available()) {
			read_char = in_read_char();
			if (read_char < '0' || read_char > '9') return *this;
		}
		else return *this;
	}
	i = read_char - '0';
	if (negative) i = -i;
	while (1) {
		if (in_read_available()) read_char = in_read_char();
		else return *this;
		if (read_char < '0' || read_char > '9') return *this;
		i *= 10;
		if (negative)i -= read_char - '0';
		else i += read_char - '0';
	}
	return *this;
}
debug_in& debug_in::operator>>(uint8_t &i) {
	*this >> (uint64_t&)i;
	return *this;
}
debug_in& debug_in::operator>>(uint16_t &i) {
	*this >> (uint64_t&)i;
	return *this;
}
debug_in& debug_in::operator>>(uint32_t &i) {
	*this >> (uint64_t&)i;
	return *this;
}
debug_in& debug_in::operator>>(uint64_t &i) {
	read_from_serial();
	i = 0;
	char read_char;
	do {
		if (!in_read_available()) return *this;
		read_char = in_read_char();
		if ((read_char >= 0 && read_char <= 32) || read_char == 127) continue;
		else break;
	} while (1);
	bool digit_detect = 0;
	if (read_char == '-');
	else if (read_char == '+');
	else if (read_char >= '0' && read_char <= '9') digit_detect = 1;
	else return *this;
	if (!digit_detect) {
		if (in_read_available()) {
			read_char = in_read_char();
			if (read_char < '0' || read_char > '9') return *this;
		}
		else return *this;
	}
	i = read_char - '0';
	while (1) {
		if (in_read_available()) read_char = in_read_char();
		else return *this;
		if (read_char < '0' || read_char > '9') return *this;
		i *= 10;
		i += read_char - '0';
	}
	return *this;
}
debug_in& debug_in::operator>>(double &i) {
	read_from_serial();
	i = 0;
	char read_char;
	do {
		if (!in_read_available()) return *this;
		read_char = in_read_char();
		if ((read_char >= 0 && read_char <= 32) || read_char == 127) continue;
		else break;
	} while (1);
	bool negative = 0, digit_detect = 0;
	if (read_char == '-') negative = 1;
	else if (read_char == '+') negative = 0;
	else if (read_char >= '0' && read_char <= '9') digit_detect = 1;
	else return *this;
	if (!digit_detect) {
		if (in_read_available()) {
			read_char = in_read_char();
			if (read_char < '0' || read_char > '9') return *this;
		}
		else return *this;
	}
	i = read_char - '0';
	if (negative) i = -i;
	while (1) {
		if (in_read_available()) read_char = in_read_char();
		else return *this;
		if (read_char < '0' || read_char > '9') break;
		i *= 10;
		if (negative)i -= read_char - '0';
		else i += read_char - '0';
	}
	if (read_char != '.')return *this;
	if (in_read_available()) {
		read_char = in_read_char();
		if (read_char < '0' || read_char > '9') return *this;
	}
	else return *this;
	int temp = 10;
	double temp2= read_char - '0';
	temp2 = (double)temp2 / (double)temp;
	if (negative) i -= temp2;
	else i += temp2;
	while (1) {
		if (in_read_available()) read_char = in_read_char();
		else return *this;
		if (read_char < '0' || read_char > '9') return *this;
		temp *= 10; 
		temp2 = read_char - '0';
		temp2 = (double)temp2 / (double)temp;
		if (negative) i -= temp2;
		else i += temp2;
	}
	return *this;
}
debug_in& debug_in::operator>>(float &i) {
	*this >> (double&)i;
	return *this;
}
debug_in& debug_in::operator>>(String &s) {
	read_from_serial();
	s = "";
	char read_char;
	do {
		if (!in_read_available()) return *this;
		read_char = in_read_char();
		if ((read_char >= 0 && read_char <= 32) || read_char == 127) continue;
		else break;
	} while (1);
	s.concat(read_char);
	while (1) {
		if (!in_read_available()) return *this;
		read_char = in_read_char();
		if ((read_char >= 0 && read_char <= 32) || read_char == 127) return *this;
		else s.concat(read_char);
	}

	return *this;
}
debug_in& debug_in::operator>>(char &c) {
	read_from_serial();
	c = 0;
	char read_char;
	do {
		if (!in_read_available()) return *this;
		read_char = in_read_char();
		if ((read_char >= 0 && read_char <= 32) || read_char == 127) continue;
		else break;
	} while (1);
	c = read_char;
	return *this;
}

bool debug_in::read_available() {
	return Serial.available() | in_read_available();
}

void debug_in::getline(String & s){
	read_from_serial();
	s = "";
	char read_char;
	while (1) {
		if (!in_read_available()) return;
		read_char = in_read_char();
		if (read_char == '\n' || read_char == '\r' || read_char == 0) return;
		else s.concat(read_char);
	}
	return;
}

void debug_in::read_from_serial(){
	while (1) {
		while (Serial.available()) {
			in_write_char(Serial.read());
		}
		delayMicroseconds(DBG_IN_READ_SERIAL_BYTE_DELAY);
		if (!Serial.available()) return;
	}
}

char debug_in::in_read_char() {
	if (!in_read_available()) return 0;
	if (in_read_idx == DBG_IN_BUFFER_LENGTH - 1) {
		in_read_idx = 0;
		return in_buffer[DBG_IN_BUFFER_LENGTH - 1];
	}
	else {
		in_read_idx++;
		return in_buffer[in_read_idx - 1];
	}
}

bool debug_in::in_read_available() {
	return in_write_idx != in_read_idx;
}

void debug_in::in_write_char(char c) {
	in_buffer[in_write_idx] = c;
	in_write_idx++;
	if (in_write_idx == DBG_IN_BUFFER_LENGTH) in_write_idx = 0;
	if (in_write_idx == in_read_idx) in_read_idx++;

	return;
}
