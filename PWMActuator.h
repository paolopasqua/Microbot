#ifndef PWM_ACTUATOR_H
#define PWM_ACTUATOR_H

/** Private Value: supply voltage of Arduino. **/
#define PRVTVL_SUPPLY_VOLT 3.7
/** Private Value: conversion factor from volts to analog pin values. **/
#define PRVTVL_VOLT_CONVERSION (PRVTVL_SUPPLY_VOLT / 255.0)

/** Private Value: engine off value. **/
#define PRVTVL_OFF_POWER (0.0 / PRVTVL_VOLT_CONVERSION) //0V
/** Private Value: minimum value writable on analog pin to turn on the engine. **/
#define PRVTVL_MIN_POWER (0.0 / PRVTVL_VOLT_CONVERSION) //2.1V //760 //3.7V
/** Private Value: maximum value writable on analog pin to turn on the engine. **/
#define PRVTVL_MAX_POWER (3.7 / PRVTVL_VOLT_CONVERSION) //3.7V //920 //4.5V

/** Private Value: conversion value from percent to power. **/
#define PRVTVL_PERCENT_CONVERSION (PRVTVL_MAX_POWER - PRVTVL_MIN_POWER)

/**
 * Class to implements a simple actuator connected to Arduino.
 * The actuator has to be only turned on or off by an analog pin. The power are set by a value in percent from 0.0f to 1.0f
 * In this settings, the motor minimum supply voltage is 3.7V while the maximum is 4.5V.
 **/
class PWMActuator {
    public:
        /**
         * Default constructor.
         **/
        PWMActuator() { }
        /**
         * Constructor.
         * pin      analog pin where the engine is connected.
         */
        PWMActuator(int pin);
        /**
         * Turning on routine. Activate the engine with the supply voltage converted from the percent.
         * NB: 0 percent DON'T equal to turn off, but it's the minimum power that the engine support.
         * powerPercent     power to apply expressed into percent from 0.0f to 1.0f
         **/
        void turnOn(float powerPercent = 0.0f);
        /**
         * Turning off routine.
         **/
        void turnOff();
    private:
        int _pin;
        int convert(float percent);
};

#endif