#ifndef RADIAL_IR_LED_H
#define RADIAL_IR_LED_H

#define RADIAL_PIN_NUM  4

/**
 * Class to implements the management of IR Led arranged in circle and turned on by digital pins of Arduino.
 * This IR Leds are grouped into unkown size groups. The class needs the number of groups that is RADIAL_PIN_NUM.
 * In this settings, there are four groups.
 **/
class RadialIRLed {
    public:
        /**
         * Default constructor.
         **/
        RadialIRLed() {}
        /**
         * Constructor.
         * pins     digital pins where the IR Led are connected.
         **/
        RadialIRLed(int pins[RADIAL_PIN_NUM]);
        /**
         * Destroyer
         **/
        ~RadialIRLed();
        /** 
         * Turning on IR Led routine. Activate to HIGH the current pin selected.
         **/
        void turnOn();
        /** 
         * Turning off IR Led routine. Activate to LOW the current pin selected.
         **/
        void turnOff();
        /** 
         * Going to next selection routine. Move the pins index to the next correct position.
         **/
        void goNext();
        /** 
         * Setting selection routine. Move the pins index to the position.
         * index    index of the pin to select.
         **/
        void setIndex(int index);
    private:
        int _pins[RADIAL_PIN_NUM];
        int _currPinInd;

};

#endif