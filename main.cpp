#include <pigpio.h>
#include <iostream>
#include <csignal>
#include "functions.h"


int main(int argc, char *argv[]) {
	if (argc < 6) {
		std::cerr << "Usage: " << argv[0] << " -m <mac_address> <intervalInSeconds> <max_temp> <min_temp>" << std::endl;
		return -1;
	}

	std::string mac_address = argv[2];
	int max_temp = std::stoi(argv[3]);
	int  min_temp = std::stoi(argv[4]);
	int intervalInSeconds = std::stoi(argv[5]);
	signal(SIGTSTP, SIG_IGN); // Ignore the SIGTSTP signal

	if (gpioInitialise() < 0) {
		std::cerr << "Failed to initialize pigpio" << std::endl;
		return -1;
	}

	setInterval([&](const std::string& mac_address, float max_temp, float min_temp) {
			signal(SIGTSTP, handleSignal);
			getInfo(mac_address, max_temp, min_temp);
	}, mac_address, max_temp, min_temp, intervalInSeconds);


	// Cleanup pigpio
	gpioTerminate();

	return 0;
}

