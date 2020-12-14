#include <Arduino.h>
#include <PID_v1.h>

#include "configPinOut.hpp"
#include "configGlobalVars.hpp"

#include "ctrlMotor.hpp"

// https://www.luisllamas.es/como-implementar-un-controlador-pid-en-arduino/

bool manMotor = false;


void tskBalanceLoop(void *pvParameters){

    // SETUP or the task
    Serial.println("Task Balance Loop on core: " + String(xPortGetCoreID()));
    TickType_t lastTime=0;
    int32_t periodMs = 10;
    TickType_t period = pdMS_TO_TICKS(periodMs);
    uint32_t debugPeriod=0;

    digitalWrite(ENABLE_MOTOR_CONTROL, LOW); // STDBY

    CtrlMotor motorControlLeft(PWM_LEFT, FORDWARD_LEFT, BACKWARD_LEFT, 0);
    CtrlMotor motorControlRight(PWM_RIGHT, FORDWARD_RIGHT, BACKWARD_RIGHT, 1);
    
    double pidSPBalance, pidRealBalance, pidOutputMotorBalance;

    gKpBalance.set(1.0);
    gKiBalance.set(0);
    gKdBalance.set(0); 

    PID PIDBalance(&pidRealBalance, &pidOutputMotorBalance, &pidSPBalance, gKpBalance.get(), gKiBalance.get(), gKdBalance.get(), DIRECT);

    pidRealBalance = 0.0;
    pidSPBalance = 0.0;
    pidOutputMotorBalance = 0.0;

    PIDBalance.SetSampleTime(periodMs*2);  
    PIDBalance.SetOutputLimits(-100, 100);
    PIDBalance.SetMode(AUTOMATIC);

    gTaskSetupFinished[TSK_BalanceLoop].set(true);

    while(1) {        
        digitalWrite(ENABLE_MOTOR_CONTROL, gEnableMotor.get());

        // TODO: Only when modified
        PIDBalance.SetTunings(gKpBalance.get(), gKiBalance.get(), gKdBalance.get()); 

        pidRealBalance = gPitch.get() * RAD_TO_DEG; // Pitch
        
        if ((debugPeriod % 1000) == 0) {
            Serial.print(" Y: ");Serial.print(gYaw.get() * RAD_TO_DEG);
            Serial.print(" P: ");Serial.print(gPitch.get() * RAD_TO_DEG);
            Serial.print(" R: ");Serial.println(gRoll.get() * RAD_TO_DEG);
        }
        
        PIDBalance.Compute();

        // Motor Control. Can be in an independent task
        if (!manMotor) {

            double totalOutputMotorLeft = pidOutputMotorBalance + gPidOutputMotorLeft.get() + gTheoricalOutputMotorLeft.get();
            double totalOutputMotorRight = pidOutputMotorBalance + gPidOutputMotorRight.get() + gTheoricalOutputMotorRight.get();

            gTotalOutputMotorLeft.set(totalOutputMotorLeft);
            gTotalOutputMotorRight.set(totalOutputMotorRight);

            motorControlLeft.writeValueEU(totalOutputMotorLeft);
            motorControlRight.writeValueEU(totalOutputMotorRight);

        } else {
            motorControlLeft.writeValueEU(50);
            motorControlRight.writeValueEU(50);
        }
        
        vTaskDelayUntil(&lastTime, period);
        debugPeriod++;
    }

}

