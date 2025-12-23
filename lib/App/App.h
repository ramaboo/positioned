#pragma once
#include <stdint.h>

class LedController;
class StepperController;
class EncoderController;
class ButtonController;

class App {
 public:
  App(LedController* ledController, StepperController* stepperController, EncoderController* encoderController, ButtonController* buttonController);

  enum class EncoderSpeed { Slow, Fast };
  enum class Direction { Off, Forward, Backward };

  void begin();
  void update();
  void validate();

 private:
  static constexpr uint32_t MAX_USER_SPEED = 10000;
  static constexpr uint32_t SLOW_SPEED_STEP = 4;
  static constexpr uint32_t FAST_SPEED_STEP = 100;
  static constexpr uint32_t INITIAL_USER_SPEED = 100;

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
  void handleSwitchBackward();
  void handleSwitchForward();
  void handleSwitchOff();

  void updateUserSpeed(int32_t value);

  LedController* _ledController;
  StepperController* _stepperController;
  EncoderController* _encoderController;
  ButtonController* _buttonController;

  EncoderSpeed _userEncoderSpeed = EncoderSpeed::Slow;

  Direction _userDirection = Direction::Off;
  Direction _currentDirection = Direction::Off;

  int32_t _userSpeed = INITIAL_USER_SPEED;
};
