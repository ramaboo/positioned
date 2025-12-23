#pragma once
#include <ESP32RotaryEncoder.h>

class EncoderController {
 public:
  EncoderController(uint8_t clkPin, uint8_t dtPin);

  static constexpr int32_t MAX_SPEED = 1;
  static constexpr int32_t MIN_SPEED = -1;

  void begin();

 private:
  RotaryEncoder _encoder;
  static void knobCallback(int32_t value);
};
