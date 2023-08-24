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


void turnOffPins() {
    gpioWrite(17, 0); // Turn off LED on GPIO 17
    gpioWrite(18, 0); // Turn off LED on GPIO 18
    gpioWrite(4, 0);  // Turn off LED on GPIO 4
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

