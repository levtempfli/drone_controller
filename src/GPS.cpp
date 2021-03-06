#include "GPS.h"

GPS_Ublox::GPS_Ublox(timer_main &tm)
    : timer_s(CFG::GPS::timer::begin_time, CFG::GPS::timer::end_time, CFG::GPS::timer::begin_block,
              CFG::GPS::timer::end_block, CFG::GPS::timer::warning_time, tm),
      timer_m(tm)
{
}

void GPS_Ublox::init()
{

    Serial1.begin(CFG::GPS::def_serial1_baud);
    Serial1.write(CFG::GPS::settings::set_baud_msg, CFG::GPS::settings::set_baud_msg_len);
    delayMicroseconds(CFG::GPS::settings::delay);
    Serial1.end();
    Serial1.begin(CFG::GPS::set_serial1_baud);

    Serial1.write(CFG::GPS::settings::enable_GNS, CFG::GPS::settings::denmea_msg_len);
    delayMicroseconds(CFG::GPS::settings::delay);
    Serial1.write(CFG::GPS::settings::enable_GSA, CFG::GPS::settings::denmea_msg_len);
    delayMicroseconds(CFG::GPS::settings::delay);
    Serial1.write(CFG::GPS::settings::enable_VTG, CFG::GPS::settings::denmea_msg_len);
    delayMicroseconds(CFG::GPS::settings::delay);

    Serial1.write(CFG::GPS::settings::disable_RMC, CFG::GPS::settings::denmea_msg_len);
    delayMicroseconds(CFG::GPS::settings::delay);
    Serial1.write(CFG::GPS::settings::disable_GGA, CFG::GPS::settings::denmea_msg_len);
    delayMicroseconds(CFG::GPS::settings::delay);
    Serial1.write(CFG::GPS::settings::disable_GLL, CFG::GPS::settings::denmea_msg_len);
    delayMicroseconds(CFG::GPS::settings::delay);
    Serial1.write(CFG::GPS::settings::disable_GSV, CFG::GPS::settings::denmea_msg_len);
    delayMicroseconds(CFG::GPS::settings::delay);
    Serial1.write(CFG::GPS::settings::disable_TXT, CFG::GPS::settings::denmea_msg_len);
    delayMicroseconds(CFG::GPS::settings::delay);

    Serial1.write(CFG::GPS::settings::set_rate_msg, CFG::GPS::settings::set_rate_msg_len);
    delayMicroseconds(CFG::GPS::settings::delay);

    in_status = 0;
    buff_i = 0;
    navMode = 1;
    PDOP = 99.99;
    lat = 0;
    lon = 0;
    alt = 0;
    kph = 0;
    numSV = 0;
    NS = 'O';
    EW = 'O';
    status = 0;
    lat_est = 0;
    lon_est = 0;
}

void GPS_Ublox::field_skip()
{
    while (buffer[res_i] != ',' && buffer[res_i] != '*')
    {
        res_i++;
    }
    res_i++;
}

uint16_t GPS_Ublox::field_get_uint16()
{
    uint16_t num = 0;
    while (buffer[res_i] != ',' && buffer[res_i] != '*')
    {
        num = num * 10 + (buffer[res_i] - 48);
        res_i++;
    }
    res_i++;
    return num;
}

double GPS_Ublox::field_get_double()
{
    double num = 0;
    bool neg = 0;
    if (buffer[res_i] == '-')
    {
        neg = 1;
        res_i++;
    }
    while (buffer[res_i] != '.' && buffer[res_i] != ',' && buffer[res_i] != '*')
    {
        num = num * 10 + (buffer[res_i] - 48);
        res_i++;
    }
    if (buffer[res_i] == ',')
    {
        res_i++;
        if (neg == 1)
            num = -num;
        return num;
    }
    res_i++;
    int32_t div = 1;
    while (buffer[res_i] != ',' && buffer[res_i] != '*')
    {
        num = num * 10 + (buffer[res_i] - 48);
        div *= 10;
        res_i++;
    }
    num /= div;
    res_i++;
    if (neg == 1)
        num = -num;
    return num;
}

char GPS_Ublox::field_get_char()
{
    char c = buffer[res_i];
    field_skip();
    return c;
}

void GPS_Ublox::decode_NMEA()
{
    res_i = 7;

    if (buffer[3] == 'G' && buffer[4] == 'S' && buffer[5] == 'A')
    {
        field_skip();

        navMode = field_get_uint16();

        for (uint8_t i = 1; i <= 12; i++)
        {
            field_skip();
        }
        PDOP = field_get_double();
    }
    else if (buffer[3] == 'G' && buffer[4] == 'N' && buffer[5] == 'S' && navMode == 3)
    {
        lat_prev = lat;
        lon_prev = lon;

        field_skip();

        lat_db = field_get_double();
        lat_db = floor(lat_db / 100) + fmod(lat_db, 100) / 60;
        NS = field_get_char();
        lat = lat_db * 10000000;
        if (NS == 'S')
            lat = -lat;

        lon_db = field_get_double();
        lon_db = floor(lon_db / 100) + fmod(lon_db, 100) / 60;
        EW = field_get_char();
        lon = lon_db * 10000000;
        if (EW == 'W')
            lon = -lon;

        field_skip();
        numSV = field_get_uint16();

        field_skip();
        alt = field_get_double();

        if (status == 0)
        {
            lat_prev = lat;
            lon_prev = lon;
            status = 1;
        }

        elapsed = timer_s.get_time_since_timestamp(1);
        lat_speed = (lat - lat_prev) / (double)elapsed;
        lon_speed = (lon - lon_prev) / (double)elapsed;

        timer_s.set_new_timestamp(1);
    }
    else if (buffer[3] == 'V' && buffer[4] == 'T' && buffer[5] == 'G' && navMode == 3)
    {
        field_skip();
        field_skip();
        field_skip();
        field_skip();
        field_skip();
        field_skip();

        kph = field_get_double();
    }
}

void GPS_Ublox::update()
{
    timer_s.begin();

    while (Serial1.available())
    {
        byte_rec = Serial1.read();
        switch (byte_rec)
        {
        case '$':
            in_status = 1;
            buff_i = 0;
            chsu = 0;
            break;
        case '*':
            if (in_status != 1)
                break;
            in_status = 2;
            break;
        default:
            switch (in_status)
            {
            case 1:
                if (buff_i == CFG::GPS::buffer_size - 1)
                {
                    in_status = 0;
                    break;
                }
                chsu ^= byte_rec;
                buff_i++;
                buffer[buff_i] = byte_rec;
                break;
            case 2:
                if (byte_rec < 58)
                    chs1 = byte_rec - 48;
                else
                    chs1 = byte_rec - 55;
                in_status = 3;
                break;
            case 3:
                if (byte_rec < 58)
                    chs2 = byte_rec - 48;
                else
                    chs2 = byte_rec - 55;
                chs1 = chs1 * 16 + chs2;
                if (chs1 == chsu)
                    decode_NMEA();
                in_status = 0;
                break;
            }
            break;
        }
        if (timer_s.warning())
            break;
    }
	
    if (navMode != 3 || timer_s.get_time_since_timestamp(1) > CFG::GPS::timeout || status == 0)
    {
        alt = 0;
        lon = 0;
        lat = 0;
        kph = 0;
        numSV = 0;
        EW = 'O';
        NS = 'O';
        PDOP = 99.99;
        status = 0;
        lat_est = 0;
        lon_est = 0;
    }
    else
    {
        lat_est = lat + trunc(lat_speed * (double)timer_s.get_time_since_timestamp(1));
        lon_est = lon + trunc(lon_speed * (double)timer_s.get_time_since_timestamp(1));
    }

    timer_s.end();
}

uint8_t GPS_Ublox::get_navMode()
{
    return navMode;
}

double GPS_Ublox::get_PDOP()
{
    return PDOP;
}

int32_t GPS_Ublox::get_lat()
{
    return lat;
}

int32_t GPS_Ublox::get_lon()
{
    return lon;
}

int32_t GPS_Ublox::get_lat_est()
{
    return lat_est;
}

int32_t GPS_Ublox::get_lon_est()
{
    return lon_est;
}

bool GPS_Ublox::get_status()
{
    return status;
}

uint8_t GPS_Ublox::get_numSV()
{
    return numSV;
}

double GPS_Ublox::get_alt()
{
    return alt;
}

double GPS_Ublox::get_kph()
{
    return kph;
}
