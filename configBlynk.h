#include <BlynkSimpleEsp32_SSL.h>
#include "configGlobalVars.hpp"

#define BLYNK_PRINT Serial // Defines the object that is used for printing
#define BLYNK_DEBUG // Optional, this enables more detailed prints

BLYNK_WRITE(V0) {
    gInputRot.set(param.asInt());
}

BLYNK_WRITE(V1) {
    gInputVel.set(param.asInt());
}

BLYNK_WRITE(V6) {
    gManualMotorLeft.set(param.asInt());
}

BLYNK_WRITE(V7) {
    gKpLeft.set(param.asFloat());
}

BLYNK_WRITE(V8) {
    gKiLeft.set(param.asFloat());
}

BLYNK_WRITE(V9) {
    gKdLeft.set(param.asFloat());
}

BLYNK_WRITE(V10) {
    gEnableMotor.set(param.asInt());
}