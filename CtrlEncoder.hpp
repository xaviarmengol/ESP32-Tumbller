#include "ESP32Encoder.h"

class CtrlEncoder
{
private:
    ESP32Encoder _encoder;
    int _pinA;
    int _pinB;
    int _pulsesPerTurn;
    double _lastHz = 0.0;
    double _historicalHz = 0.0;

    int64_t _lastValue = 0;
    int64_t _lastMillis = 0;

public:
    CtrlEncoder(int pinA, int pinB, int pulsesPerTurn);
    ~CtrlEncoder();
    void calcHz();
    double getHz();
    int64_t getValue();
    void println();
};
