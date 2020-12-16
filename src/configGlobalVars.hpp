#pragma once

//#include "Arduino.h"
#include "SharedVar.hpp"

enum TaskNames {TSK_6050, TSK_BalanceLoop, TSK_VelLoop, TSK_Wifi, TSK_Inputs};

extern SharedVar<bool> gTaskSetupFinished[5];

extern SharedVar<int> gInputRot;
extern SharedVar<int> gInputVel;

extern SharedVar<double> gSetpointHzLeft;
extern SharedVar<double> gRealHzLeft;

extern SharedVar<double> gPidOutputMotorLeft;
extern SharedVar<double> gTheoricalOutputMotorLeft;

extern SharedVar<double> gManualMotorLeft;

extern SharedVar<double> gKpLeft;
extern SharedVar<double> gKiLeft;
extern SharedVar<double> gKdLeft;


extern SharedVar<double> gSetpointHzRight;
extern SharedVar<double> gRealHzRight;

extern SharedVar<double> gPidOutputMotorRight;
extern SharedVar<double> gTheoricalOutputMotorRight;

extern SharedVar<double> gManualMotorRight;

extern SharedVar<double> gKpRight;
extern SharedVar<double> gKiRight;
extern SharedVar<double> gKdRight;


extern SharedVar<double> gKpBalance;
extern SharedVar<double> gKiBalance;
extern SharedVar<double> gKdBalance;

extern SharedVar<int> gEnableMotor;

extern SharedVar<double> gYaw;
extern SharedVar<double> gPitch;
extern SharedVar<double> gRoll;

extern SharedVar<double> gTotalOutputMotorLeft;
extern SharedVar<double> gTotalOutputMotorRight;





