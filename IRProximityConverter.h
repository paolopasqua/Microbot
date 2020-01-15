#ifndef IR_PROXIMITY_CONVERTER_H
#define IR_PROXIMITY_CONVERTER_H

#define TOLLERANCE  50
#define DEFAULT_AMBIENT_VALUE 40

class IRProximityConverter {
    public:
        static int booleanConversion(int value, int ambientValue = DEFAULT_AMBIENT_VALUE);
        static void booleanConversion(int* values, int length, int ambientValue = DEFAULT_AMBIENT_VALUE);

        static int distanceConversion(int value, int ambientValue = DEFAULT_AMBIENT_VALUE);
        static void distanceConversion(int* values, int length, int ambientValue = DEFAULT_AMBIENT_VALUE);
        
    private:

};

#endif