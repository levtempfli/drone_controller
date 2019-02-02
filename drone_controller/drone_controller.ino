#include "escct.h"
#include "timer_main.h"
#include "I2C_manager.h"

escct escct_o;

timer_main _timer_m;
i2c_manager _i2c_mng;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	delay(10000);
}


void loop() {
	_i2c_mng.i2c_init();

	_timer_m.turn_begin();
	escct_o.start_motors();
	digitalWrite(LED_BUILTIN, HIGH);
	_timer_m.turn_end();
	delay(2000);

	_timer_m.turn_begin();
	digitalWrite(LED_BUILTIN, LOW);
	escct_o.set_throttle(400, 400, 400, 400);
	_timer_m.turn_end();
	delay(2000);

	_timer_m.turn_begin();
	digitalWrite(LED_BUILTIN, LOW);
	escct_o.set_throttle(800, 800, 800, 800);
	_timer_m.turn_end();
	delay(2000);



	escct_o.stop_motors();
	digitalWrite(LED_BUILTIN, LOW);
	delay(5000);

}
