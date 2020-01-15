#include "PWMActuator.h"
#include <Arduino.h>

PWMActuator::PWMActuator(int pin) {
    _pin = pin;
    pinMode(pin, OUTPUT);
    analogWrite(pin, PRVTVL_OFF_POWER);
}

void PWMActuator::turnOn(float powerPercent = 0.0f) {
    int value = 0;

    if (powerPercent < 0)
        powerPercent = 0;
    else if (powerPercent > 1)
        powerPercent = 1;
    value = convert(powerPercent);

    analogWrite(_pin, value);
}

void PWMActuator::turnOff() {
    analogWrite(_pin, PRVTVL_OFF_POWER);
}

int PWMActuator::convert(float percent) {
    return PRVTVL_MIN_POWER + PRVTVL_PERCENT_CONVERSION * percent;
}