#include <Arduino.h>
#include <PID_v1.h>

#include "ctrlEncoder.hpp"

#include "configPinOut.hpp"
#include "configGlobalVars.hpp"

// https://www.luisllamas.es/como-implementar-un-controlador-pid-en-arduino/

constexpr int PULSES_PER_TURN = 780; // 780 calculated
constexpr int PWM_PER_HZ = 50;     // Constant = PWM (0..100) / Hz

// 50 -> -1,25 // 75 -> -2,14 // -> from 35 to 40 without load. With load aprox 50

double hzToEUaproximation(double hz);

void tskVelLoop(void *pvParameters){

    // SETUP or the task
    Serial.println("Task VelControl on core: " + String(xPortGetCoreID()));
    TickType_t lastTime=0;
    int32_t periodMs = 20;
    TickType_t period = pdMS_TO_TICKS(periodMs);

    CtrlEncoder encoderLeft(ENCODER_LEFT_A, ENCODER_LEFT_B, PULSES_PER_TURN);
    CtrlEncoder encoderRight(ENCODER_RIGHT_A, ENCODER_RIGHT_B, PULSES_PER_TURN);

    
    double pidSetpointHzLeft, pidRealHzLeft, pidOutputMotorLeft, theoricalOutputMotorLeft;
    double KpLeft=1, KiLeft=0, KdLeft=0; //Specify the links and initial tuning parameter
    PID PIDVelLeft(&pidRealHzLeft, &pidOutputMotorLeft, &pidSetpointHzLeft, KpLeft, KiLeft, KdLeft, DIRECT);

    pidRealHzLeft = 0.0;
    pidSetpointHzLeft = 0.0;
    pidOutputMotorLeft = 0.0;
    theoricalOutputMotorLeft = hzToEUaproximation(pidSetpointHzLeft);

    PIDVelLeft.SetSampleTime(periodMs*2);  
    PIDVelLeft.SetOutputLimits(-100, 100);
    PIDVelLeft.SetMode(AUTOMATIC);

    double pidSetpointHzRight, pidRealHzRight, pidOutputMotorRight, theoricalOutputMotorRight;
    double KpRight=1, KiRight=0, KdRight=0; //Specify the links and initial tuning parameter
    PID PIDVelRight(&pidRealHzRight, &pidOutputMotorRight, &pidSetpointHzRight, KpRight, KiRight, KdRight, DIRECT);

    pidRealHzRight = 0.0;
    pidSetpointHzRight = 0.0;
    pidOutputMotorRight = 0.0;
    theoricalOutputMotorRight = hzToEUaproximation(pidSetpointHzRight);

    PIDVelRight.SetSampleTime(periodMs*2);  
    PIDVelRight.SetOutputLimits(-100, 100);
    PIDVelRight.SetMode(AUTOMATIC);

    gTaskSetupFinished[TSK_VelLoop].set(true);
   
    while(1) {

        digitalWrite(ENABLE_MOTOR_CONTROL, gEnableMotor.get());

        KpLeft = gKpLeft.get()*50.0; // 5
        KiLeft = gKiLeft.get()*50.0; // 0.3
        KdLeft = gKdLeft.get(); // 0.4
        // TODO: Only when modified
        PIDVelLeft.SetTunings(KpLeft, KiLeft, KdLeft); 

        encoderLeft.calcHz();
        pidRealHzLeft = encoderLeft.getHz();

        // Input is -100 to 100 -> -2 Hz to +2 Hz
        pidSetpointHzLeft = static_cast<double>(gInputVel.get()) / 50.0;

        PIDVelLeft.Compute();

        // Feedfordward based on formula
        theoricalOutputMotorLeft = hzToEUaproximation(pidSetpointHzLeft);

        ////

        KpRight = gKpRight.get()*50.0; // 5
        KiRight = gKiRight.get()*50.0; // 0.3
        KdRight = gKdRight.get(); // 0.4
        // TODO: Only when modified
        PIDVelRight.SetTunings(KpRight, KiRight, KdRight); 

        encoderRight.calcHz();
        pidRealHzRight = encoderRight.getHz();

        // Input is -100 to 100 -> -2 Hz to +2 Hz
        pidSetpointHzRight = static_cast<double>(gInputVel.get()) / 50.0;

        PIDVelRight.Compute();

        // Feedfordward based on formula
        theoricalOutputMotorRight = hzToEUaproximation(pidSetpointHzRight);

        ////


        // Move to global vars
        gRealHzLeft.set(pidRealHzLeft);
        gSetpointHzLeft.set(pidSetpointHzLeft);
        gPidOutputMotorLeft.set(pidOutputMotorLeft);
        gTheoricalOutputMotorLeft.set(theoricalOutputMotorLeft);

        gRealHzRight.set(pidRealHzRight);
        gSetpointHzRight.set(pidSetpointHzRight);
        gPidOutputMotorRight.set(pidOutputMotorRight);
        gTheoricalOutputMotorRight.set(theoricalOutputMotorRight);

        vTaskDelayUntil(&lastTime, period);
    }

}

// TODO: Calculate the right value!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Aproximate the hz value to a -100...100 range. The relation is known experimentally.

double hzToEUaproximation(double hz) {
    return (hz * PWM_PER_HZ);
}
