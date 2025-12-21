#pragma once
#include <AceButton.h>
using namespace ace_button;
#include <FastAccelStepper.h>

class ButtonController {
public:
  ButtonController(uint8_t backPin, uint8_t controlPin, uint8_t forwardPin, uint8_t encoderPin);
  void begin();
  void loop();
  void setStepper(FastAccelStepper* stepper);

private:
  ButtonConfig _backConfig;
  ButtonConfig _controlConfig;
  ButtonConfig _forwardConfig;
  ButtonConfig _encoderConfig;

  AceButton _backButton;
  AceButton _controlButton;
  AceButton _forwardButton;
  AceButton _encoderButton;

  uint8_t _backPin;
  uint8_t _controlPin;
  uint8_t _forwardPin;
  uint8_t _encoderPin;

  static void handleBackEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
  static void handleControlEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
  static void handleForwardEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
  static void handleEncoderEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);

  static FastAccelStepper* s_stepper;
};
