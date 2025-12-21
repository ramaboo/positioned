#pragma once
#include "Event.h"

class LedController;
class StepperController;
class EncoderController;
class ButtonController;

class App {
public:
  App(LedController* ledController, StepperController* stepperController, EncoderController* encoderController, ButtonController* buttonController);

  void begin();
  void update();

  void onBackPressed();
  void onBackReleased();
  void onControlPressed();
  void onControlReleased();
  void onForwardPressed();
  void onForwardReleased();
  void onEncoderPressed();
  void onEncoderReleased();
  void onEncoderTurn(uint32_t value);

private:
  void handleBackPressed();
  void handleBackReleased();
  void handleControlPressed();
  void handleControlReleased();
  void handleForwardPressed();
  void handleForwardReleased();
  void handleEncoderPressed();
  void handleEncoderReleased();
  void handleEncoderTurn(uint32_t value);

  LedController* _ledController;
  StepperController* _stepperController;
  EncoderController* _encoderController;
  ButtonController* _buttonController;
  enum class State { Idle, Running };
  State _state = State::Idle;
};
