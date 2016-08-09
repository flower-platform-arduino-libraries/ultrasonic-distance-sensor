/*
 *  Author: Anca Barbu
 */
#define SHORTEST_DELAY 29
#include <NewPing.h>
#include <Arduino.h> 
 
 class UltrasonicDistanceSensor : public NewPing {
	private:
		unsigned long lastTimestamp = 0;
	public:
		UltrasonicDistanceSensor(uint8_t trigger_pin, uint8_t echo_pin, unsigned int max_cm_distance);
		/*
		 * Send a ping and get the echo time (in microseconds) as a result. [max_cm_distance] allows you to optionally set a new max distance.
		 */
		unsigned int ping(unsigned int max_cm_distance = 0);
		/*
		 * Send a ping and get the distance in whole inches. [max_cm_distance] allows you to optionally set a new max distance.
		 */
		unsigned long ping_cm(unsigned int max_cm_distance = 0);
		/*
		 * Send a ping and get the distance in whole centimeters. [max_cm_distance] allows you to optionally set a new max distance.
		 */
		unsigned long ping_in(unsigned int max_cm_distance = 0);		
};
 
UltrasonicDistanceSensor::UltrasonicDistanceSensor(uint8_t trigger_pin, uint8_t echo_pin, unsigned int max_cm_distance) : NewPing(trigger_pin, echo_pin, max_cm_distance) {
	Serial.println("Constructor");
}

unsigned int UltrasonicDistanceSensor::ping(unsigned int max_cm_distance) {
	unsigned long currentTimestamp = millis();
	unsigned long delayBetweenPings = currentTimestamp - lastTimestamp; 
	if (delayBetweenPings < SHORTEST_DELAY) { //29ms should be the shortest delay between pings
		delay(SHORTEST_DELAY - delayBetweenPings);
	}
	lastTimestamp  = millis();
	return NewPing::ping(max_cm_distance);	
}

unsigned long UltrasonicDistanceSensor::ping_cm(unsigned int max_cm_distance) {
	unsigned long echoTime = UltrasonicDistanceSensor::ping(max_cm_distance); // Calls the ping method and returns with the ping echo distance in uS.
#if ROUNDING_ENABLED == false
	return (echoTime / US_ROUNDTRIP_CM);              // Call the ping method and returns the distance in centimeters (no rounding).
#else
	return NewPingConvert(echoTime, US_ROUNDTRIP_CM); // Convert uS to centimeters.
#endif
}


unsigned long UltrasonicDistanceSensor::ping_in(unsigned int max_cm_distance) {
	unsigned long echoTime = UltrasonicDistanceSensor::ping(max_cm_distance); // Calls the ping method and returns with the ping echo distance in uS.
#if ROUNDING_ENABLED == false
	return (echoTime / US_ROUNDTRIP_IN);              // Call the ping method and returns the distance in inches (no rounding).
#else
	return NewPingConvert(echoTime, US_ROUNDTRIP_IN); // Convert uS to inches.
#endif
}

	