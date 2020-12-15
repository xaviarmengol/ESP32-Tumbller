#include "CtrlMotor.hpp"

double mapDouble(double x, double in_min, double in_max, double out_min, double out_max);

CtrlMotor::~CtrlMotor() {}

CtrlMotor::CtrlMotor(int pinPWM, int pinFordward, int pinBackward, int pwmChannel, int freq, int resolution) {
    this->_pinFordward = pinFordward;
    this->_pinBackward = pinBackward;
    this->_pinPWM = pinPWM;
    this->_freq = freq;
    this->_resolution = resolution;
    

    this->_maxvalue = pow(2, resolution);

    if (pwmChannel<16 && pwmChannel>=0) {
        this->_pwmChannel = pwmChannel;
    } else {
        this->_pwmChannel = 0;
        Serial.println("Channel should be between 0..15. Channel 0 assigned.");
    }

    ledcSetup(_pwmChannel, freq, resolution);
    ledcAttachPin(pinPWM, _pwmChannel);
    Serial.print("Pin: "); Serial.print(pinPWM); Serial.print(" assigned to channel PWM: "); Serial.println(_pwmChannel);

}

void CtrlMotor::writeRawValue (int32_t pwmValue, bool fordward, bool backward){
    digitalWrite(_pinFordward, fordward);
    digitalWrite(_pinBackward, backward);
    ledcWrite(_pwmChannel, abs(pwmValue));
}

void CtrlMotor::writeValue (int32_t value) {

    int pwmValue = constrain(value, -1 * _maxvalue, _maxvalue);

    if (pwmValue >= 0) {
        writeRawValue(pwmValue, true, false);

    } else {
        writeRawValue(pwmValue, false, true);

    }

}

void CtrlMotor::writeValueEU (double value) {

    double pwmValueDouble = mapDouble(constrain(value, -100.0, 100.0), -100.0, 100.0, -1 * _maxvalue, _maxvalue);

    int pwmValue = static_cast<int>(pwmValueDouble);

    if (pwmValue >= 0) {
        writeRawValue(pwmValue, true, false);
    } else {
        writeRawValue(pwmValue, false, true);
    }

}

int32_t CtrlMotor::getMaxValue(){
    return(_maxvalue);
}

// Convert Engineering Units to PWMValue, based on the choosed resolution

int32_t CtrlMotor::convertEUtoValue(int32_t valueEU) {
    return (constrain(map(valueEU, -100, 100, -1.0*_maxvalue, _maxvalue), -1.0*_maxvalue, _maxvalue));
}

double mapDouble(double x, double in_min, double in_max, double out_min, double out_max)
{
 return (double)(x - in_min) * (out_max - out_min) / (double)(in_max - in_min) + out_min;
}



