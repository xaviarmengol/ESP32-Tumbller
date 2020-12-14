#include <Arduino.h>
#include "configBlynk.h"
#include "wifiUtils.h"
#include "configGlobalVars.hpp"

void tskWifi(void *pvParameters){

    // SETUP or the task
    Serial.println("Task Wifi on core: " + String(xPortGetCoreID()));
    TickType_t lastTime=0;
    TickType_t period = pdMS_TO_TICKS(200);
    unsigned long periods=0;

    InitWifi();

    // Blynk configuration

    Blynk.config(auth);

    gTaskSetupFinished[TSK_Wifi].set(true);

    while(true){

        if ((periods % 2) == 0 ) {
            
            Blynk.virtualWrite(V2, gSetpointHzLeft.get());
            Blynk.virtualWrite(V3, gRealHzLeft.get());

            Blynk.virtualWrite(V4, gPidOutputMotorLeft.get());
            Blynk.virtualWrite(V5, gTheoricalOutputMotorLeft.get());
           
        }

        Blynk.run();
        vTaskDelayUntil(&lastTime, period);
        periods++;
    }


}
