#include <Arduino.h>
#undef min
#undef max

#include "debug_in.h"
#include "debug_out.h"
#include "timer_main.h"
#include "timer_sub.h"

void setup()
{
    delay(2000);
    debug_out dout;
    debug_in din;
    timer_main tim_ma;
    timer_sub sub(1000, 2000, 1, 1, 1500, tim_ma);

    while (1)
    {
        tim_ma.turn_begin();
        dout << tim_ma.get_turn_time() << " ";
        sub.begin();
        sub.end();
        dout << tim_ma.get_turn_time() << " ";

        dout << tim_ma.get_main_errors() << " " << tim_ma.get_sub_errors() << "\n";

        tim_ma.turn_end();
    }
}

void loop()
{
    exit(0);
}