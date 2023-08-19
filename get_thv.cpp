#include "get_thv.h"
#include "constants.h" 

GetValue::GetValue(const std::string& hex_value) {
    std::string temperature_hex = hex_value.substr(temperature_hex_start, temperature_hex_length);
    int temperature_dec = HexToDec(temperature_hex);
    if (temperature_dec > max_int) {
        temperature_dec -= offset;
    }
    temperature = static_cast<float>(temperature_dec) / temperature_divider;

    std::string humidity_hex = hex_value.substr(humidity_hex_start, humidity_hex_length);
    humidity = HexToDec(humidity_hex);

    std::string voltage_hex = hex_value.substr(voltage_hex_start, voltage_hex_length);
    int voltage_dec = HexToDec(voltage_hex);
    voltage = voltage_offset + (static_cast<float>(voltage_dec) * voltage_multiplier);
}

float GetValue::getTemperature() const {
    return temperature;
}

float GetValue::getHumidity() const {
    return humidity;
}

float GetValue::getVoltage() const {
    return voltage;
}

