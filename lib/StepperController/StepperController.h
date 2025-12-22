#pragma once
#include <FastAccelStepper.h>

class StepperController {
 public:
  StepperController(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin);
  void begin();

  void setSpeed(uint32_t speed);
  void runForward();
  void runBackward();
  void stop();
  bool isRunning();

 private:
  uint8_t _stepPin;
  uint8_t _dirPin;
  uint8_t _enablePin;
  static FastAccelStepper* s_stepper;
};
