#pragma once
#include <Arduino.h>

class LedController;
class StepperController;
class EncoderController;
class ButtonController;

class App {
public:
  static void setLedController(LedController* ledController);
  static void setStepperController(StepperController* stepperController);
  static void setEncoderController(EncoderController* encoderController);
  static void setButtonController(ButtonController* buttonController);

  static void init();
  static void loop();

  static App& get();

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

  static LedController* s_ledController;
  static StepperController* s_stepperController;
  static EncoderController* s_encoderController;
  static ButtonController* s_buttonController;
};
