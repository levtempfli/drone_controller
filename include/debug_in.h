#ifndef DEBUG_IN
#define DEBUG_IN
#include <Arduino.h>
#undef min
#undef max
#include "config.h"

// Debug read class
class debug_in
{
  public:
    debug_in(){};
    debug_in(const debug_in &) = delete;
    // read ints
    debug_in &operator>>(int &i);
    debug_in &operator>>(int8_t &i);
    debug_in &operator>>(int16_t &i);
    debug_in &operator>>(int32_t &i);
    debug_in &operator>>(int64_t &i);
    // read uints
    debug_in &operator>>(uint8_t &i);
    debug_in &operator>>(uint16_t &i);
    debug_in &operator>>(uint32_t &i);
    debug_in &operator>>(uint64_t &i);
    // read floats
    debug_in &operator>>(double &i);
    debug_in &operator>>(float &i);

    debug_in &operator>>(String &s); // read string
    debug_in &operator>>(char &c);   // read char
    void in_write_char(char c);      // write char to in buffer
    bool read_available();           // any data available for read
    void getline(String &s);         // getline

  private:
    void read_from_serial();                    // read every data from serial
    char in_read_char();                        // read char from in buffer
    bool in_read_available();                   // any data availabe in read buffer
    char in_buffer[CFG::Dbg::in_buffer_length]; // write from RPI, read from program
    uint32_t in_write_idx = 0;                  // in buffer write index
    uint32_t in_read_idx = 0;                   // in buffer read index
};

#endif // !DEBUG_IN
