#ifndef GET_THV_H
#define GET_THV_H

#include "hex_to_dec.h"
#include "constants.h"
class SensorData {
	public:
		SensorData(const std::string& hex_value);

		float getTemperature() const;
		float getHumidity() const;
		float getVoltage() const;

	private:
		float _temperature;
		float _humidity;
		float _voltage;
};

#endif

