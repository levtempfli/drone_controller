#include <Arduino.h>
#undef min
#undef max

#include "debug_in.h"
#include "debug_out.h"

void setup()
{
    delay(5000);
    // put your setup code here, to run once:
    debug_out dout;
    debug_in din;
    double a=0;
    delay(10000);
    while (1)
    {
        if (din.read_available())
        {
            din >> a;
        }
        dout << a << "\n";
        delay(4);
    }
}

void loop()
{
    exit(0);
}