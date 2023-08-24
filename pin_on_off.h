#ifndef PIN_ON_OFF_H
#define PIN_ON_OFF_H

#include <pigpio.h>
#include <unistd.h>

inline void  pinOn(size_t pin){
	gpioWrite(pin, 1);
}

int main()
{
	for(int i = 0;i < 4;i++){	
		if (gpioInitialise() < 0)
		{
			// Initialization failed
			return 1;
		}

		// Define GPIO pins for LEDs
		int redLedPin = 4;
		int greenLedPin = 17;
		int blueLedPin = 18;

		// Set GPIO pins as output
		gpioSetMode(redLedPin, PI_OUTPUT);
		gpioSetMode(greenLedPin, PI_OUTPUT);
		gpioSetMode(blueLedPin, PI_OUTPUT);

		// Turn on each LED for 1 second and then turn it off
		gpioWrite(redLedPin, 1);
		usleep(1000000);  // 1 second
		gpioWrite(redLedPin, 0);

		gpioWrite(greenLedPin, 1);
		usleep(1000000);  // 1 second
		gpioWrite(greenLedPin, 0);

		gpioWrite(blueLedPin, 1);
		usleep(1000000);  // 1 second
		gpioWrite(blueLedPin, 0);
	}
	// Cleanup and release resources
	gpioTerminate();

	return 0;
}

#endif 
