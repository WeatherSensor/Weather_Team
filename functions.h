#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <thread>
#include "hex_to_dec.h"
#include "get_data.h"
#include "get_thv.h"
#include <csignal>
#include <regex>
#include <functional>
#include <string>
#include <pigpio.h>

bool keepRunning = true;

inline void handleSignal(int signum) {
    if (signum == SIGTSTP) {
        std::cout << "Ctrl+Z pressed. Cleaning up and terminating..." << std::endl;
        gpioWrite(25, 0);
        gpioWrite(17, 0);
        gpioWrite(18, 0); 
        gpioWrite(4, 0);
        gpioTerminate();
	exit(0);
    }
}


inline void getInfo(const std::string& mac_address, const float max_temp, const float min_temp){

/*	if (gpioInitialise() < 0) {
		std::cerr << "Failed to initialize pigpio" << std::endl;
		return -1;
	}
*/
	std::string data = get_data(mac_address);
	if (data == "F") {
		std::cerr << "Trying To Connect To The Sensor..." << std::endl;
		std::cout << std::endl;
		return;
	}

	SensorData values(data);

	std::cout << "Value: " << data;
	std::cout << "Voltage: " << values.getVoltage() << "mV" << std::endl;
	std::cout << "Humidity: " << values.getHumidity() << "%" << std::endl;
	std::cout << "Temperature: " << values.getTemperature() << " degrees Celsius" << std::endl;
	std::cout << std::endl;

	if (max_temp > values.getTemperature() && values.getTemperature() > min_temp) {
		gpioWrite(25, 0);
		gpioWrite(17, 0);
		gpioWrite(18, 0);
		gpioWrite(4, 1);
	}

	else if(max_temp< values.getTemperature()) {

		gpioWrite(4, 0);
		gpioWrite(18, 0);
		gpioWrite(25, 1);
		while(true){
			gpioDelay(300000);
			gpioWrite(17, 1);
			gpioDelay(300000);
			gpioWrite(17, 0);

		}
	}

	else {

		gpioWrite(25, 1);
		gpioWrite(4, 0);
		gpioWrite(17, 0);

		while(true){
			gpioDelay(300000);
			gpioWrite(18, 1);
			gpioDelay(300000);
			gpioWrite(18, 0);

		}
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
void setInterval(Callable func, const std::string& mac_address, int intervalInSeconds, int max_temp, int min_temp) {
	while (keepRunning) {
		// Call the provided function with the given arguments
		func(mac_address, max_temp, min_temp);

		// Wait for the specified interval
		std::this_thread::sleep_for(std::chrono::seconds(intervalInSeconds));
	}
}

#endif

