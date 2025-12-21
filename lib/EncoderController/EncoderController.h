#pragma once
#include <ESP32RotaryEncoder.h>
#include <FastAccelStepper.h>

class EncoderController {
public:
  EncoderController(uint8_t clkPin, uint8_t dtPin);
  void begin();
  void setStepper(FastAccelStepper* stepper);

private:
  RotaryEncoder _encoder;
  static FastAccelStepper* s_stepper;
  static void knobCallback(uint32_t value);
};
