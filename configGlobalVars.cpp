#include "configGlobalVars.hpp"
#include "SharedVar.hpp"


SharedVar<bool> gTaskSetupFinished[5]; 

SharedVar<int> gInputRot; // -100 to 100
SharedVar<int> gInputVel; // -100 to 100


SharedVar<double> gSetpointHzLeft;
SharedVar<double> gRealHzLeft;

SharedVar<double> gPidOutputMotorLeft;
SharedVar<double> gTheoricalOutputMotorLeft;

SharedVar<double> gManualMotorLeft;

SharedVar<double> gKpLeft;
SharedVar<double> gKiLeft;
SharedVar<double> gKdLeft;


SharedVar<double> gSetpointHzRight;
SharedVar<double> gRealHzRight;

SharedVar<double> gPidOutputMotorRight;
SharedVar<double> gTheoricalOutputMotorRight;

SharedVar<double> gManualMotorRight;

SharedVar<double> gKpRight;
SharedVar<double> gKiRight;
SharedVar<double> gKdRight;


SharedVar<double> gKpBalance;
SharedVar<double> gKiBalance;
SharedVar<double> gKdBalance;

SharedVar<int> gEnableMotor;

SharedVar<double> gYaw;
SharedVar<double> gPitch;
SharedVar<double> gRoll;

SharedVar<double> gTotalOutputMotorLeft;
SharedVar<double> gTotalOutputMotorRight;




