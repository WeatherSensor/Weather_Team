#include "get_thv.h"
#include "get_data.h"
#include <iostream>
#include <regex>      // For regular expressions
#include <csignal>    // For signal handling
#include <thread>     // For sleep_for
#include <chrono>     // For chrono literals

bool keepRunning = true;

void signalHandler(int signal) {
    if (signal == SIGINT || signal == SIGTSTP) {
        std::cout << "Press 'q' or 'quit' to exit." << std::endl;
    }
}

bool isValidMacAddress(const std::string &mac) {
    // Regular expression pattern for a valid MAC address
    std::regex macPattern("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
    return std::regex_match(mac, macPattern);
}

int main() {
    std::string mac_address;
    std::string input;

    signal(SIGINT, signalHandler);   // Set up signal handler for Ctrl+C
    signal(SIGTSTP, signalHandler);  // Set up signal handler for Ctrl+Z

    while (keepRunning) {
        std::cout << "Enter The MAC Address (or 'q' to quit): ";
        std::cin >> input;

        if (input == "q" || input == "quit") {
            keepRunning = false; // Exit the loop if 'q' or 'quit' is entered
        } else if (isValidMacAddress(input)) {
            mac_address = input;
            while (keepRunning) {
                std::string data = get_data(mac_address);
                if (data == "F") {
                    return -1;
                }
                std::cout << "Value: " << data << std::endl;

                GetValue values(data);
                // Process the values as needed

                std::cout << "Voltage: " << values.getVoltage() << "mV" << std::endl;
                std::cout << "Humidity: " << values.getHumidity() << "%" << std::endl;
                std::cout << "Temperature: " << values.getTemperature() << " degrees Celsius" << std::endl;
                std::cout << std::endl;

                // Wait for 5 seconds
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        } else {
            std::cout << "Invalid input. Please enter a valid MAC address or 'q' to quit." << std::endl;
        }
    }

    return 0;
}

