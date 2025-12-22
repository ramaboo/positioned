#pragma once
#include <stdint.h>

class LedController;
class StepperController;
class EncoderController;
class ButtonController;

class App {
 public:
  App(LedController* ledController, StepperController* stepperController, EncoderController* encoderController, ButtonController* buttonController);

  void begin();
  void update();

 private:
  void handleBackwardPressed();
  void handleBackwardReleased();
  void handleForwardPressed();
  void handleForwardReleased();
  void handleStartStopPressed();
  void handleStartStopReleased();
  void handleEncoderPressed();
  void handleEncoderReleased();
  void handleEncoderTurn(uint32_t value);
  void handleSwitchBackward();
  void handleSwitchForward();
  void handleSwitchOff();

  LedController* _ledController;
  StepperController* _stepperController;
  EncoderController* _encoderController;
  ButtonController* _buttonController;
  enum class State { Idle, Running };
  State _state = State::Idle;

  enum class Direction { None, Forward, Backward };
  Direction _direction = Direction::None;

  uint32_t _currentSpeed = 0;
};
