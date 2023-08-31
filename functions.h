#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <thread>
#include "get_data.h"
#include "get_thv.h"
#include <csignal>
#include <regex>
#include <functional>
#include <string>
#include <pigpio.h>


bool IntervalCheck = true;
bool keepRunning = true;

inline void handleSignal(int signum) {
	if (signum == SIGTSTP && gpioRead(buzzer_pin) == 1) {
		std::cout << std::endl << "Ctrl+Z pressed. Buzzer is turning off ..." << std::endl;
		gpioWrite(buzzer_pin, 0);
	}
	else if (signum == SIGINT){
		std::cout << std::endl << "Ctrl+C pressed. Cleaning up..." << std::endl;
		gpioWrite(buzzer_pin, 0);		
		gpioWrite(red_led_pin, 0);
		gpioWrite(blue_led_pin, 0);
		gpioWrite(green_led_pin, 0);
		gpioTerminate();
		exit(0);
	}
}



inline void getInfo(const std::string& mac_address, const float max_temp, const float min_temp, const size_t IntervalSeconds){

	std::string data = get_data(mac_address);
	if (data == "F") {
		std::cerr << "Trying To Connect To The Sensor..." << std::endl;
		std::cout << std::endl;
		return;
	}

	SensorData values(data);
/*
	std::cout << "Value: " << data;
	std::cout << "Voltage: " << values.getVoltage() << "mV" << std::endl;
	std::cout << "Humidity: " << values.getHumidity() << "%" << std::endl;
	std::cout << "Temperature: " << values.getTemperature() << " degrees Celsius" << std::endl;
	std::cout << std::endl;
*/
	if (max_temp > values.getTemperature() && values.getTemperature() > min_temp) {
		gpioWrite(buzzer_pin, 0);
		gpioWrite(red_led_pin, 0);
		gpioWrite(blue_led_pin, 0);
		gpioWrite(green_led_pin, 1);
		IntervalCheck = false;

	}

	else if(values.getTemperature() > max_temp) {

		gpioWrite(green_led_pin, 0);
		gpioWrite(blue_led_pin, 0);
		gpioWrite(buzzer_pin, 1);

		for (int i = 0;i < IntervalSeconds;i++){
			gpioDelay(leds_blink_seconds);
			gpioWrite(red_led_pin, 1);
			gpioDelay(leds_blink_seconds);
			gpioWrite(red_led_pin, 0);

		}
		gpioWrite(buzzer_pin, 0);

		IntervalCheck = true;
	}

	else {

		gpioWrite(buzzer_pin, 1);
		gpioWrite(green_led_pin, 0);
		gpioWrite(red_led_pin, 0);

		for (int i = 0;i < IntervalSeconds;i++){
			gpioDelay(leds_blink_seconds);
			gpioWrite(blue_led_pin, 1);
			gpioDelay(leds_blink_seconds);
			gpioWrite(blue_led_pin, 0);

		}
		gpioWrite(buzzer_pin, 0);

		IntervalCheck = true;

	}

}

// Function to validate MAC address using regular expression
inline bool isValidMacAddress(const std::string &mac) {
	// Regular expression pattern for a valid MAC address
	std::regex macPattern("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
	return std::regex_match(mac, macPattern);
}

// Interval function that calls a given function at specified intervals
template <typename Callable>
inline void setInterval(Callable func, const std::string& mac_address, int intervalInSeconds, int max_temp, int min_temp) {
	while (keepRunning) {
		// Call the provided function with the given arguments
		func(mac_address, max_temp, min_temp, intervalInSeconds);
	
		if (IntervalCheck == false){	
			std::this_thread::sleep_for(std::chrono::seconds(intervalInSeconds));
		}
	}
}

#endif

