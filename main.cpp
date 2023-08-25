#include <iostream>
#include <csignal>
#include "functions.h"

int main(int argc, char *argv[]) {
    // Check if there are enough command-line arguments
    if (argc != 3 || std::string(argv[1]) != "-m") {
        std::cerr << "Usage: " << argv[0] << " -m \"mac address\"" << std::endl;
        return -1;
    }

    std::string mac_address = argv[2]; // Get the MAC address from command-line argument

	//signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
    // Start the interval function with a 5-second interval
    setInterval([&mac_address]() {
            retrieveAndPrintData(mac_address);
            }, 20);

    return 0;
}

