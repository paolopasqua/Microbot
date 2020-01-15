#include "RadialIRProximity.h"
#include <Arduino.h>
#include "RadialIRLed.h"


RadialIDProximity::RadialIDProximity(int emitPins[COMMAND_PIN_NUM], int recPins[COMMAND_PIN_NUM], int readPins[READ_PIN_NUM], int readingNums = READING_DEFAULT_PRECISION) {
    _emit = RadialIRLed(emitPins);
    _rec = RadialIRLed(recPins);
    for (int i = 0; i < READ_PIN_NUM; i++) {
        _readPins[i] = readPins[i];
        pinMode(readPins[i], INPUT);
    }
    _readingNums = readingNums;
}

RadialIDProximity::~RadialIDProximity() {

}

int* RadialIDProximity::read(int group = -1) {
    int groupToRead = COMMAND_PIN_NUM;

    if (group >= 0 && group < COMMAND_PIN_NUM) {
        _emit.setIndex(group);
        _rec.setIndex(group);
        
        groupToRead = group + 1; //to end after one reading
    } else {
        group = 0;
    }

    for (; group < groupToRead; group++) {
        readGroup(group);
        _emit.goNext();
        _rec.goNext();
    }

    return _values;
}

int RadialIDProximity::readAmbient() {
    int value = 0;
    _rec.turnOn();
    delay(2);

    for(int group = 0; group < COMMAND_PIN_NUM; group++) {
        for(int readInd = 0; readInd < READ_PIN_NUM; readInd++) {
            value += analogRead(_readPins[readInd]);
            delay(1); //to correct read
        }
        _rec.goNext();
    }

    _rec.turnOff();
    
    value /= RADIAL_PRECISION;
    return value;
}

void RadialIDProximity::readGroup(int currGroup) {
    //tot time estimated: 4ms + 2ms*_readingNums + 2ms
    _emit.turnOn();
    _rec.turnOn();
    delay(2);

    for(int readInd = 0; readInd < READ_PIN_NUM; readInd++) {
        //value index: group + readInd*NUM_GROUP
        //so at every reading it moves forward of COMMAND_PIN_NUM (number of groups) from the group position base.
        int valueInd = currGroup + readInd*COMMAND_PIN_NUM;
        int value = 0;

        for(int k = 0; k < _readingNums; k++) {
            value += analogRead(_readPins[readInd]);
            delay(1); //to correct read
        }

        value /= _readingNums; //making average
        _values[valueInd] = value; //saving
        //conversion to volts: 0.0048828125
    }

    _emit.turnOff();
    _rec.turnOff();
}