#include "get_thv.h"

SensorData::SensorData(const std::string& hex_value) {
	std::string temperature_hex = hex_value.substr(temperature_hex_start, temperature_hex_length);
	int temperature_dec = HexToDec(temperature_hex);
	if (temperature_dec > max_int) {
		temperature_dec -= offset;
	}
	_temperature = static_cast<float>(temperature_dec) / temperature_divider;

	std::string humidity_hex = hex_value.substr(humidity_hex_start, humidity_hex_length);
	_humidity = HexToDec(humidity_hex);

	std::string voltage_hex = hex_value.substr(voltage_hex_start, voltage_hex_length);
	const int voltage_dec = HexToDec(voltage_hex);
	_voltage = voltage_offset + (static_cast<float>(voltage_dec) * voltage_multiplier);
}

float SensorData::getTemperature() const {
	return _temperature;
}

float SensorData::getHumidity() const {
	return _humidity;
}

float SensorData::getVoltage() const {
	return _voltage;
}

