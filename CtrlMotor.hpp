#include <Arduino.h>

class CtrlMotor
{
private:

    int _pwmChannel;
    int _pinFordward;
    int _pinBackward;
    int _pinPWM;
    int _freq;
    int _resolution;
    int32_t _maxvalue;

public:

    ~CtrlMotor();
    CtrlMotor(int pinPWM, int pinFordward, int pinBackward, int pwmChannel, int freq = 5000, int resolution=12);
    void writeRawValue (int32_t pwmValue, bool fordward, bool backward);
    void writeValue (int32_t value);
    void writeValueEU(double value);
    int32_t getMaxValue();
    int32_t convertEUtoValue(int32_t valueEU);

};
