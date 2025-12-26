#pragma once
#include <Arduino.h>

#include "Types.h"

class SwitchController {
 public:
  SwitchController(uint8_t backwardPin, uint8_t forwardPin);
  void begin();
  void update();

  Direction getDirection();

 private:
  static constexpr uint32_t DEBOUNCE_MS = 50;

  uint8_t _backwardPin;
  uint8_t _forwardPin;

  Direction _lastDirection = Direction::Off;
  uint32_t _lastChangeAtMs = 0;
};
