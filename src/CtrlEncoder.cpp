#include "CtrlEncoder.hpp"

CtrlEncoder::CtrlEncoder(int pinA, int pinB, int pulsesPerTurn) {
    ESP32Encoder::useInternalWeakPullResistors=UP;
    _encoder.attachHalfQuad(pinA, pinB);
    _pinA = pinA;
    _pinB = pinB;
    _pulsesPerTurn = pulsesPerTurn;
}

CtrlEncoder::~CtrlEncoder() {
}

int64_t CtrlEncoder::getValue() {
    return(_encoder.getCount());
}
void CtrlEncoder::calcHz() {

    double currentHz;
    
    int64_t deltaMillis = millis() - _lastMillis;
    int64_t currentValue = _encoder.getCount();
    int64_t deltaPulses = currentValue - _lastValue;
    _lastValue = currentValue;

    if (deltaMillis == 0) {
        //Serial.println("Encoder: Too fast calculation. Divide by Zero.");
        
    } else {
        _lastMillis = millis();
        currentHz = (double)(deltaPulses * 1000.0) / ((double)deltaMillis * (double)_pulsesPerTurn);

        // Filter
        _lastHz = _historicalHz*0.5 + currentHz*(1.0 - 0.5);
        _historicalHz = _lastHz;
    }
    
}

void CtrlEncoder::println() {
    String msg = String("Encoder " + String(_pinA) + String(" Val: ") + String((int)getValue()) + String(" Hz: ") + String(_lastHz));
    Serial.println(msg);
}

double CtrlEncoder::getHz() {
    return(_lastHz);
}
