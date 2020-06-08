#include <Arduino.h>
#undef min
#undef max
#include "debug_out.h"
#include "config.h"

//Constructor
debug_out::debug_out()
{
    Serial.begin(CFG::Dbg::serial0_baud_rate);
}

//Print ints
debug_out &debug_out::operator<<(int i)
{
    *this << (int64_t)i;
    return *this;
}
debug_out &debug_out::operator<<(int8_t i)
{
    *this << (int64_t)i;
    return *this;
}
debug_out &debug_out::operator<<(int16_t i)
{
    *this << (int64_t)i;
    return *this;
}
debug_out &debug_out::operator<<(int32_t i)
{
    *this << (int64_t)i;
    return *this;
}
debug_out &debug_out::operator<<(int64_t i)
{
    double tmp;
    double tmp2 = 1;
    if (i < 0)
    {
        i = -i;
        *this << (char)'-';
    }
    tmp = i;
    i = i / 10;
    while (i >= 1)
    {
        tmp2 = tmp2 * 10;
        i = i / 10;
    }
    i = tmp;
    while (tmp2 != 0)
    {
        tmp = (int64_t)(i / tmp2) % 10 + 48;
        tmp2 = (int64_t)tmp2 / 10;
        *this << (char)tmp;
    }
    return *this;
}

//Print uints
debug_out &debug_out::operator<<(uint8_t i)
{
    *this << (uint64_t)i;
    return *this;
}
debug_out &debug_out::operator<<(uint16_t i)
{
    *this << (uint64_t)i;
    return *this;
}
debug_out &debug_out::operator<<(uint32_t i)
{
    *this << (uint64_t)i;
    return *this;
}
debug_out &debug_out::operator<<(uint64_t i)
{
    double tmp;
    double tmp2 = 1;
    tmp = i;
    i = i / 10;
    while (i >= 1)
    {
        tmp2 = tmp2 * 10;
        i = i / 10;
    }
    i = tmp;
    while (tmp2 != 0)
    {
        tmp = (uint64_t)(i / tmp2) % 10 + 48;
        tmp2 = (uint64_t)tmp2 / 10;
        *this << (char)tmp;
    }
    return *this;
}

//Print floats
debug_out &debug_out::operator<<(double i)
{

    double tmp;
    double tmp2 = 1;
    if (i < 0)
    {
        i = -i;
        *this << (char)'-';
    }
    tmp = i;
    i = i / 10;
    while (i >= 1)
    {
        tmp2 = tmp2 * 10;
        i = i / 10;
    }
    i = tmp;

    while (tmp2 != 0)
    {
        tmp = (uint64_t)(i / tmp2) % 10 + 48;
        tmp2 = (uint64_t)tmp2 / 10;
        *this << (char)tmp;
    }
    if (precision <= 0)
        return *this;
    *this << (char)'.';
    i = i - (uint64_t)i;
    tmp2 = i;
    tmp = precision;
    while (tmp > 0)
    {
        if (tmp != 1)
        {
            tmp2 *= 10;
            *this << (char)(tmp2 + '0');
            tmp2 = tmp2 - (uint64_t)tmp2;
        }
        else
        {
            tmp2 *= 10;
            switch (round_mode)
            {
            case 1:
                i += 0.00000000001; /// WTF
                tmp2 = (uint64_t)(tmp2 - fmod(i, 1));
                break;
            case 2:
                tmp2 = (uint64_t)(tmp2 + 0.5f);
                if (tmp2 > 9)
                    tmp2 = 9;
                break;
            }

            *this << (char)(tmp2 + '0');
        }

        tmp--;
    }
    return *this;
}
debug_out &debug_out::operator<<(float i)
{
    *this << (double)i;
    return *this;
}

//Print string
debug_out &debug_out::operator<<(String s)
{
    for (uint64_t i = 0; i < s.length(); i++)
    {
        *this << (char)s[i];
    }
    return *this;
}

//Print char
debug_out &debug_out::operator<<(char c)
{
    out_write_char(c);
    if (c != 0)
        Serial.write(c);
    return *this;
}

//Set precision of float
void debug_out::set_precision(int8_t pr)
{
    if (pr < 0)
        precision = 0;
    else if (pr > CFG::Dbg::out_max_precision)
        precision = CFG::Dbg::out_max_precision;
    else
        precision = pr;
}

//Set round mode of float
void debug_out::set_round_mode(int8_t m)
{
    if (m != 1 && m != 2)
        return;
    round_mode = m;
}

//Fatal error, endless loop
void debug_out::fatal_error(String s)
{
    Serial2.begin(CFG::Serial::serial2_baud_rate);
    String s2 = "";
    s2.concat("@DBG#");
    s2.concat(s);
    s2.concat("#~NA");
    while (1)
    {
        Serial.println(s);
        Serial2.print(s2);
        delayMicroseconds(CFG::Dbg::out_fatal_loop_wait);
    }
}

//Read the outbut buffer2
char debug_out::out_read_char()
{
    if (!out_read_available())
        return 0;
    if (out_read_idx == CFG::Dbg::out_buffer_length - 1)
    {
        out_read_idx = 0;
        return out_buffer[CFG::Dbg::out_buffer_length - 1];
    }
    else
    {
        out_read_idx++;
        return out_buffer[out_read_idx - 1];
    }
}

//Returns wheter new data is available int the buffer2
bool debug_out::out_read_available()
{
    return out_write_idx != out_read_idx;
}

//Write to serial and output buffer2
void debug_out::out_write_char(char c)
{
    out_buffer[out_write_idx] = c;
    out_write_idx++;
    if (out_write_idx == CFG::Dbg::out_buffer_length)
        out_write_idx = 0;
    if (out_write_idx == out_read_idx)
        out_read_idx++;

    return;
}