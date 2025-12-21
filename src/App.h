#pragma once
#include <stdint.h>

class LedController;
class StepperController;
class EncoderController;
class ButtonController;

class App {
public:
  static void init(LedController* led, StepperController* stepperCtrl, EncoderController* encoder, ButtonController* buttons);
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
  App(LedController* led, StepperController* stepperCtrl, EncoderController* encoder, ButtonController* buttons);

  LedController* _led;
  StepperController* _stepperCtrl;
  EncoderController* _encoder;
  ButtonController* _buttons;
};
