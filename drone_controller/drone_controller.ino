#include "escct.h"
#include "timer_main.h"
#include "I2C_manager.h"
#include "I2C1_manager.h"

escct escct_o;

timer_main _timer_m;
i2c_manager _i2c_mng;
i2c1_manager _i2c1_mng;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	delay(10000);
}


void loop() {
	_i2c_mng.i2c_init();
	_i2c1_mng.i2c_init();

	_timer_m.turn_begin();
	escct_o.start_motors();
	digitalWrite(LED_BUILTIN, HIGH);
	_timer_m.turn_end();
	delay(2000);

	_timer_m.turn_begin();
	digitalWrite(LED_BUILTIN, LOW);
	escct_o.set_throttle(100, 350, 600, 850);
	_timer_m.turn_end();
	delay(2000);

	_timer_m.turn_begin();
	digitalWrite(LED_BUILTIN, LOW);
	escct_o.set_throttle(850, 600, 350, 100);
	_timer_m.turn_end();
	delay(2000);



	escct_o.stop_motors();
	digitalWrite(LED_BUILTIN, LOW);
	delay(5000);

}
