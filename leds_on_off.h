#ifndef LEDS_ON_OFF_H
#define LEDS_ON_OFF_H

#include <wiringPi.h>
#include <cstddef>


void TurnOn(const size_t pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
}

void TurnOff(const size_t pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

#endif

