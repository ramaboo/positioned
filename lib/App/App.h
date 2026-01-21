#pragma once
#include <stdint.h>

#include "ButtonController.h"
#include "EncoderController.h"
#include "LedController.h"
#include "StepperController.h"
#include "SwitchController.h"
#include "Types.h"

class App {
 public:
  App(ButtonController* buttonController, EncoderController* encoderController, LedController* ledController, StepperController* stepperController,
      SwitchController* switchController);

  void begin();
  void update();
  void validate();

 private:
  static constexpr int32_t MAX_USER_SPEED = 10000;
  static constexpr int32_t MIN_USER_SPEED = 1;
  static constexpr int32_t INITIAL_USER_SPEED = 100;

  static constexpr int32_t SLOW_SPEED_STEP = 4;
  static constexpr int32_t FAST_SPEED_STEP = 100;

  void handleBackwardPressed();
  void handleBackwardReleased();
  void handleForwardPressed();
  void handleForwardReleased();
  void handleStartStopPressed();
  void handleStartStopReleased();
  void handleEncoderPressed();
  void handleEncoderReleased();
  void handleEncoderTurnRight(int32_t value);
  void handleEncoderTurnLeft(int32_t value);
  void handleSwitchOff();
  void handleSwitchForward();
  void handleSwitchBackward();

  void updateUserSpeed(int32_t value);
  void processEvents();

  LedController* _ledController;
  StepperController* _stepperController;
  EncoderController* _encoderController;
  ButtonController* _buttonController;
  SwitchController* _switchController;

  EncoderSpeed _userEncoderSpeed = EncoderSpeed::Slow;

  Direction _userDirection = Direction::Off;
  Direction _currentDirection = Direction::Off;

  int32_t _userSpeed = INITIAL_USER_SPEED;
};
