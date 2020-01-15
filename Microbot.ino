#include <Arduino.h>
#include "RadialIRProximity.h"
#include "IRProximityConverter.h"
#include "PWMActuator.h"

#define LED_ON_MAX  1
#define LED_ON_MED  0.3l
#define LED_ON_MIN  0.05f

const int LED_BUITIN = 13;
const int EMITTERS_PINS[] = {2,3,4,5};
const int RECEIVERS_PINS[] = {12,8,7,6};
const int READING_PINS[] = {A0,A1,A2};
const int PWM_PINS[] = {9,10,11};

RadialIDProximity prox(EMITTERS_PINS, RECEIVERS_PINS, READING_PINS, 2);
PWMActuator led0(PWM_PINS[0]);
PWMActuator led1(PWM_PINS[1]);
PWMActuator led2(PWM_PINS[2]);
int ambientValue;

void setup() {
    //Serial.begin(9600);
    //Serial.println("Starting program.");

    delay(3000);

    pinMode(LED_BUITIN, OUTPUT);

    digitalWrite(LED_BUITIN, HIGH);
    delay(500);
    ambientValue = prox.readAmbient();
    digitalWrite(LED_BUITIN,LOW);
    delay(100);
}

void loop() {
    //Reads the proximity values
    int* values = prox.read();

    //Converts the proximity values into boolean values (there's something or not)
    IRProximityConverter::booleanConversion(values, RADIAL_PRECISION, ambientValue);

    /*5
    Index disposition:
          3
     X  2   4 
      1       5 Z
    0           6
      11      7
        10  8
        Y 9

    led0 -> X
    led1 -> Y
    led2 -> Z
    */

    if (values[1] == 1 || values[2] == 1) {
        led0.turnOn(LED_ON_MAX);
    } else if (values[0] == 1 || values[3] == 1) {
        led0.turnOn(LED_ON_MED);
    } else if (values[11] == 1 || values[4]) {
        led0.turnOn(LED_ON_MIN);
    } else {
        led0.turnOff();
    }
   
    if (values[5] == 1 || values[6] == 1) {
        led2.turnOn(LED_ON_MAX);
    } else if (values[4] == 1 || values[7] == 1) {
        led2.turnOn(LED_ON_MED);
    } else if (values[3] == 1 || values[8]) {
        led2.turnOn(LED_ON_MIN);
    } else {
        led2.turnOff();
    }

    if (values[9] == 1 || values[10] == 1) {
        led1.turnOn(LED_ON_MAX);
    } else if (values[8] == 1 || values[11] == 1) {
        led1.turnOn(LED_ON_MED);
    } else if (values[7] == 1 || values[0]) {
        led1.turnOn(LED_ON_MIN);
    } else {
        led1.turnOff();
    }
    
}