#pragma once
#include <ESP32RotaryEncoder.h>

class EncoderController {
 public:
  EncoderController(uint8_t clkPin, uint8_t dtPin);
  void begin();

 private:
  RotaryEncoder _encoder;
  static void knobCallback(uint32_t value);
};
