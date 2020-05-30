#include "sonar.h"

void sonar::init(){
	pinMode(SONAR_TRIGGER_PIN, OUTPUT); // Sets the trigPin as an Output
	pinMode(SONAR_ECHO_PIN, INPUT); // Sets the echoPin as an Input
	duration = 0;
	distance = 0;
	timer_s.set_new_timestamp(0);
	on_the_ground = 0;
}

void sonar::update() {
	timer_s.begin();
	
	digitalWrite(SONAR_TRIGGER_PIN, LOW); // Clears the trigPin
	delayMicroseconds(SONAR_DELAY_AFTER_CLEAR); 
	digitalWrite(SONAR_TRIGGER_PIN, HIGH);// Sets the trigPin on HIGH state for 10 micro seconds
	delayMicroseconds(SONAR_DELAY_AFTER_TRIGGER);
	digitalWrite(SONAR_TRIGGER_PIN, LOW);
	
	duration = pulseIn(SONAR_ECHO_PIN, HIGH, SONAR_WAIT_FOR_SIGNAL_TIMEOUT);// Reads the echoPin, returns the sound wave travel time in microseconds
	distance = duration * SONAR_SOUND_DISTANCE_IN_1MS / 2;// Calculating the distance

	if (distance < SONAR_MAX_DISTANCE_FROM_GROUND && distance != 0) {
		timer_s.set_new_timestamp(0);
		on_the_ground = 1;
	}
	if (timer_s.get_time_since_timestamp(0) > SONAR_DATA_TIMEOUT) {
		on_the_ground = 0;
	}

	
	timer_s.end();
}

bool sonar::is_it_on_the_ground(){
	return on_the_ground;
}


