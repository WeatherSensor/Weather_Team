#include <iostream>
#include <csignal>
#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " -m \"mac_address\" <max_temp> <min_temp>" << std::endl;
        return -1;
    }

    std::string mac_address = argv[2];
    int max_temp_size = std::stoi(argv[3]);
    int min_temp_size = std::stoi(argv[4]);
    int intervalInSeconds = 20; // Set the interval value as needed

    //signal(SIGINT, SIG_IGN); // Ignore the SIGINT signal
    signal(SIGTSTP, SIG_IGN); // Ignore the SIGTSTP signal

    setInterval([&](const std::string& mac_address, int max_temp, int min_temp) {
        retrieveAndPrintData(mac_address, max_temp, min_temp);
    }, mac_address, intervalInSeconds, max_temp_size, min_temp_size);

    return 0;
}

