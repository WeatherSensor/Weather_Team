#ifndef GET_VALUE_H
#define GET_VALUE_H

#include "hex_to_dec.h"

class GetValue {
    public:
        GetValue(const std::string& hex_value);

        float getTemperature() const;
        float getHumidity() const;
        float getVoltage() const;

    private:
        float temperature;
        float humidity;
        float voltage;
};

#endif

