#include <Arduino.h>
#undef min
#undef max

#include "I2C1_manager.h"
#include "I2C_manager.h"
#include "debug_in.h"
#include "debug_out.h"
#include "escct.h"
#include "timer_main.h"
#include "timer_sub.h"

debug_out *dout_p;
debug_in *din_p;

void setup()
{
    // Declarations
    timer_main tim_ma;
    escct esc(tim_ma);

    i2c_manager i2c0;
    i2c1_manager i2c1;

    debug_out dout;
    debug_in din;
    dout_p = &dout;
    din_p = &din;

    // Pre-Init Delay
    delay(5000);
    // Init
    i2c0.i2c_init();
    i2c1.i2c_init();

    // Fast-Init

    // Loop

    while (1)
    {
        esc.start_motors();
        int tm = micros();
        esc.set_throttle(0, 0, 0, 0);
        dout << micros() - tm << "\n";
        delayMicroseconds(4000);
    }

    /*while (1)
    {
        tim_ma.turn_begin();

        tim_ma.turn_end();
    }*/
}

void loop()
{
    exit(0);
}