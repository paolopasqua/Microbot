#include "IRProximityConverter.h"
#include <Arduino.h>

int IRProximityConverter::booleanConversion(int value, int ambientValue = DEFAULT_AMBIENT_VALUE) {
    if (value > ambientValue + TOLLERANCE) {
        return 1;
    }
    return 0;
}

void IRProximityConverter::booleanConversion(int* values, int length, int ambientValue = DEFAULT_AMBIENT_VALUE) {
    int tmp = 0;

    for (int i = 0; i < length; i++) {
        tmp = booleanConversion(values[i], ambientValue);
        values[i] = tmp;
    }
}

int IRProximityConverter::distanceConversion(int value, int ambientValue = DEFAULT_AMBIENT_VALUE) {
    return 0; //TODO
}

void IRProximityConverter::distanceConversion(int* values, int length, int ambientValue = DEFAULT_AMBIENT_VALUE) {
    int tmp = 0;

    for (int i = 0; i < length; i++) {
        tmp = distanceConversion(values[i], ambientValue);
        values[i] = tmp;
    }
}