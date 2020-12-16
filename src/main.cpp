
//https://www.luisllamas.es/obtener-orientacion-y-altitud-ahrs-con-imu-9dof-y-rtimulib-arduino/

#include <Arduino.h>
#include "configPinOut.hpp"
#include "configGlobalVars.hpp"

TaskHandle_t handTsk6050;
void tsk6050 (void *pvParameters);

TaskHandle_t handTskVelLoop;
void tskVelLoop (void *pvParameters);

TaskHandle_t handTskBalanceLoop;
void tskBalanceLoop (void *pvParameters);

TaskHandle_t handTskWifi;
void tskWifi (void *pvParameters);

TaskHandle_t handTskInputs;
void tskInputs (void *pvParameters);


void setup() {

    Serial.begin(115200);

    pinModeConfig();
    
    // Control tsk in 0, others in 1 (Arduino)

    xTaskCreateUniversal(tsk6050, "Tsk6050", 10000, NULL, 3, &handTsk6050, 0);
    delay(1000);
    while (!gTaskSetupFinished[TSK_6050].get()) {}
    Serial.println("Task6050 OK");

    xTaskCreateUniversal(tskBalanceLoop, "TskBalanceLoop", 10000, NULL, 2, &handTskVelLoop, 0);
    delay(1000);
    while (!gTaskSetupFinished[TSK_BalanceLoop].get()) {}
    Serial.println("TaskBalanceLoop OK");

    xTaskCreateUniversal(tskVelLoop, "TskVelLoop", 10000, NULL, 1, &handTskVelLoop, 0);
    delay(1000);
    while (!gTaskSetupFinished[TSK_VelLoop].get()) {}
    Serial.println("Task Vel Loop OK");

    xTaskCreateUniversal(tskWifi, "TaskWifi", 10000, NULL, 0, &handTskWifi, 1);
    delay(1000);
    while (!gTaskSetupFinished[TSK_Wifi].get()) {}
    Serial.println("Task Wifi OK");

    //xTaskCreateUniversal(tskInputs, "TaskInputs", 10000, NULL, 0, &handTskInputs, 1);
    //delay(2000);

    Serial.println("Setup end");
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(10000));
}
