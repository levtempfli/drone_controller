#ifndef DEBUG_OUT
#define DEBUG_OUT
#include <Arduino.h>
#undef min
#undef max
#include "config.h"
// Debug print class
class debug_out
{
  public:
    debug_out(const debug_out &) = delete;
    debug_out(); // Constructor
    // Print ints
    debug_out &operator<<(int i);
    debug_out &operator<<(int8_t i);
    debug_out &operator<<(int16_t i);
    debug_out &operator<<(int32_t i);
    debug_out &operator<<(int64_t i);
    // Print uints
    debug_out &operator<<(uint8_t i);
    debug_out &operator<<(uint16_t i);
    debug_out &operator<<(uint32_t i);
    debug_out &operator<<(uint64_t i);
    // Print floats
    debug_out &operator<<(double i);
    debug_out &operator<<(float i);

    debug_out &operator<<(String s); // Print string
    debug_out &operator<<(char c);   // Print char
    void set_precision(int8_t pr);   // Set precision of float
    void set_round_mode(int8_t m);   // Set round mode of float
    void fatal_error(String s);      // Fatal error, endless loop
    char out_read_char();            // Read the outbut buffer2
    bool out_read_available();       // Returns wheter new data is available int the buffer2

  private:
    void out_write_char(char c);                      // Write to serial and output buffer2
    char out_buffer[CFG::Dbg::out_buffer_length];     // write from program, read from RPI com
    uint32_t out_write_idx = 0;                       // rotation buffer write index
    uint32_t out_read_idx = 0;                        // rotation buffer read index
    int8_t precision = CFG::Dbg::out_def_precision;   // set precision
    int8_t round_mode = CFG::Dbg::out_def_round_mode; // set round mode
};

#endif // !DEBUG_OUT
