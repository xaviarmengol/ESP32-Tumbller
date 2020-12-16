#include <Arduino.h>
#include <PID_v1.h>

#include "configPinOut.hpp"
#include "configGlobalVars.hpp"

#include "Ctrl6050.hpp"

void tsk6050 (void *pvParameters){

    // SETUP or the task
    Serial.println("Task 6050 Loop on core: " + String(xPortGetCoreID()));
    TickType_t lastTime=0;
    TickType_t period = 1; //pdMS_TO_TICKS(periodMs);

    setup6050();

    gTaskSetupFinished[TSK_6050].set(true);

    while(1) {

        bool updated = loop6050();

        if (updated) {
            gYaw.set(ypr[0]);
            gPitch.set(ypr[1]);
            gRoll.set(ypr[2]);
        }

        vTaskDelayUntil(&lastTime, period);
    }

}
