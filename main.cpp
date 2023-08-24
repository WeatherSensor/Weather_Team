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
	    
	    gpioWrite(25, 1);
            gpioWrite(4, 0);
            gpioWrite(18, 0);
            gpioWrite(17, 1);
        }
	
	else {
	    
	    gpioWrite(25, 1);
	    gpioWrite(4, 0);
            gpioWrite(17, 0);
            gpioWrite(18, 1);
        }
    }, mac_address, max_temp, min_temp, intervalInSeconds);


    // Cleanup pigpio
    gpioTerminate();

    return 0;
}

