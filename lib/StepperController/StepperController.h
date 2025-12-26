#pragma once
#include <FastAccelStepper.h>

#include "Types.h"

class StepperController {
 public:
  static constexpr int32_t ACCELERATION = 1000;

  StepperController(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin);
  void begin();
  void validate();

  void setSpeed(int32_t speed);
  void runForward();
  void runBackward();
  void stop();
  bool isRunning();

  Direction getDirection();

 private:
  uint8_t _stepPin;
  uint8_t _dirPin;
  uint8_t _enablePin;
  static FastAccelStepper* s_stepper;
};
