#include "functions.h"


int main(int argc, char *argv[]) {
	if (argc < 6) {
		std::cerr << "Usage: " << argv[0] << " -m <mac_address> <intervalInSeconds> <max_temp> <min_temp>" << std::endl;
		return -1;
	}

	std::string mac_address = argv[2];
	float max_temp = std::stoi(argv[3]);
	float  min_temp = std::stoi(argv[4]);
	size_t intervalInSeconds = std::stoi(argv[5]);

	if (gpioInitialise() < 0) {
		std::cerr << "Failed to initialize pigpio" << std::endl;
		return -1;
	}

	setInterval([&](const std::string& mac_address, float max_temp, float min_temp, size_t intervalInSeconds) {
			signal(SIGINT, handleSignal);
			signal(SIGTSTP, handleSignal);
			getInfo(mac_address, max_temp, min_temp, intervalInSeconds);
	}, mac_address, max_temp, min_temp, intervalInSeconds);


	gpioTerminate();

	return 0;
}
