#include "RadialIRLed.h"
#include <Arduino.h>

RadialIRLed::RadialIRLed(int pins[RADIAL_PIN_NUM]) {
    for(int i = 0; i < RADIAL_PIN_NUM; i++) {
        _pins[i] = pins[i];
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], LOW);
    }

    _currPinInd = 0;
}

RadialIRLed::~RadialIRLed() {

}

void RadialIRLed::turnOn() {
    digitalWrite(_pins[_currPinInd], HIGH);
}

void RadialIRLed::turnOff() {
    digitalWrite(_pins[_currPinInd], LOW);
}

void RadialIRLed::goNext() {
    _currPinInd = (_currPinInd + 1 < RADIAL_PIN_NUM) ? _currPinInd + 1 : 0;
}

void RadialIRLed::setIndex(int index) {
    if (index >= 0 && index < RADIAL_PIN_NUM)
        _currPinInd = index;
}