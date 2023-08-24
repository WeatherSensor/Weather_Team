#include "get_thv.h"
#include "get_data.h"
#include <iostream>
#include <regex>
#include <csignal>    // For signal handling
#include <thread>     // For sleep_for
#include <chrono>     // For chrono literals

bool keepRunning = true;

// Signal handler function to respond to Ctrl+Z
void signalHandler(int signal) {
    if (signal == SIGINT || signal == SIGTSTP) {
        keepRunning = false;
        std::cout << " Stopping..." << std::endl;
    }
}

// Function to validate MAC address using regular expression
bool isValidMacAddress(const std::string &mac) {
    // Regular expression pattern for a valid MAC address
    std::regex macPattern("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
    return std::regex_match(mac, macPattern);
}

// Function to retrieve and print data
void retrieveAndPrintData(const std::string &mac_address) {
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
}

// Interval function that calls a given function at specified intervals
template <typename Callable>
void setInterval(Callable func, int intervalInSeconds) {
    while (keepRunning) {
        func(); // Call the provided function

        // Wait for the specified interval
        std::this_thread::sleep_for(std::chrono::seconds(intervalInSeconds));
    }
}

int main(int argc, char *argv[]) {
    // Check if there are enough command-line arguments
    if (argc != 3 || std::string(argv[1]) != "-m") {
        std::cerr << "Usage: " << argv[0] << " -m \"mac address\"" << std::endl;
        return -1;
    }

    std::string mac_address = argv[2]; // Get the MAC address from command-line argument

    signal(SIGTSTP, signalHandler);  // Set up signal handler for Ctrl+Z
    signal(SIGINT, signalHandler);   // Set up signal handler for Ctrl+c

    // Start the interval function with a 5-second interval
    setInterval([&mac_address]() {
            retrieveAndPrintData(mac_address);
            }, 20);

    return 0;
}

