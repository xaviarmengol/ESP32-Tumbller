
#include <Arduino.h>
#include "configPinOut.hpp"

void pinModeConfig () {

    pinMode(FORDWARD_LEFT, OUTPUT);
    pinMode(BACKWARD_LEFT, OUTPUT);

    pinMode(FORDWARD_RIGHT, OUTPUT);
    pinMode(BACKWARD_RIGHT, OUTPUT);

    pinMode(ENABLE_MOTOR_CONTROL, OUTPUT);
    
    pinMode(ENCODER_LEFT_A, INPUT);
    pinMode(ENCODER_LEFT_B, INPUT);

    pinMode(ENCODER_RIGHT_A, INPUT);
    pinMode(ENCODER_RIGHT_B, INPUT);

    //pinMode(INTERRUPT_PIN, INPUT);

}


