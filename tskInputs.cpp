#include <Arduino.h>

#include "configPinOut.hpp"
#include "configGlobalVars.hpp"
#include "CtrlPulsesInput.hpp"

void tskInputs(void *pvParameters){

    // SETUP or the task
    Serial.println("Task Inputs on core: " + String(xPortGetCoreID()));
    TickType_t lastTime=0;
    int32_t periodMs = 100;
    TickType_t period = pdMS_TO_TICKS(periodMs);

    int32_t maxHz = 100; // Hz * 1000
    int32_t maxHzYaw = 100; // Yaw (hz) * 1000

    rmtInit();

    while(1) {

        gInputRot.set(rmtMapConstrain(0, -maxHz, maxHz));
        gInputVel.set(rmtMapConstrain(1, -maxHzYaw, maxHzYaw));

        vTaskDelayUntil(&lastTime, period);
    }

}
