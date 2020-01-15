#ifndef RADIAL_ID_PROXIMITY_H
#define RADIAL_ID_PROXIMITY_H

#include "RadialIRLed.h"

/** Number of pins to command the IR Led (= number of IR Led groups) **/
#define COMMAND_PIN_NUM RADIAL_PIN_NUM
/** Number of pins where read values (= number of IR Led for each group) **/
#define READ_PIN_NUM 3
/** Number of values read by the class. There are four IR Led groups each made of three IR Led. **/
#define RADIAL_PRECISION 12
/** Default value for the readingNums parameter of the constructor: reads for each IR Led group five times and does the average. **/
#define READING_DEFAULT_PRECISION 5

/**
 * Class to implements the IR proximity sensor made of IR Leds arranged in circle.
 * This IR Leds are grouped and the reading are made at the "same time" for one Led for each group. The reading repeats this operation
 * for each Led in the groups.
 * The Leds are turned on by digital pins of Arduino, while the reading is made with the analog pins of Arduino.
 * In this settings, there are three IR Leds into each group and four groups. So there are three pins to read from values (one for Led in
 * a group) and twelve values to save.
 **/
class RadialIDProximity {
    public:
        /**
         * Constructor.
         * emitPins     array of digital pins to activate emitters IR group (ordered by the reading sequence)
         * recPins      array of digital pins to activate receivers IR group (ordered by the reading sequence)
         * readPins     array of analog pins where read the values
         * readingNums  number of times to repeat reading for each IR led group
         **/
        RadialIDProximity(int emitPins[COMMAND_PIN_NUM], int recPins[COMMAND_PIN_NUM], int readPins[READ_PIN_NUM], int readingNums = READING_DEFAULT_PRECISION);
        /**
         * Destroyer.
         **/
        ~RadialIDProximity();
        /**
         * Reading values routine. Activates IR led to read the proximity of objects around.
         * group        specify a IR led group to refresh only their proximity value. Default value -1 stands for all groups.
         * 
         * Returns the pointer to the array of the values read. 
         **/
        int* read(int group = -1);
        /**
         * Reading ambient values routine. Activates only IR reader led to read the ambient irradiation.
         * 
         * Return the average of all the reading.
         **/
        int readAmbient();
    private:
        RadialIRLed _emit;
        RadialIRLed _rec;
        int _readPins[READ_PIN_NUM];
        int _values[RADIAL_PRECISION];
        int _readingNums;

        void readGroup(int currGroup);
};

#endif