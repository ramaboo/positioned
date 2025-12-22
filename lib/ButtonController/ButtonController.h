#pragma once
#include <AceButton.h>
using namespace ace_button;

class ButtonController {
 public:
  ButtonController(uint8_t backwardPin, uint8_t forwardPin, uint8_t startStopPin, uint8_t encoderPin, uint8_t backwardSwitchPin, uint8_t forwardSwitchPin);
  void begin();
  void update();

 private:
  ButtonConfig _backwardConfig;
  ButtonConfig _forwardConfig;
  ButtonConfig _startStopConfig;
  ButtonConfig _encoderConfig;
  ButtonConfig _backwardSwitchConfig;
  ButtonConfig _forwardSwitchConfig;

  AceButton _backwardButton;
  AceButton _forwardButton;
  AceButton _startStopButton;
  AceButton _encoderButton;
  AceButton _backwardSwitch;
  AceButton _forwardSwitch;

  uint8_t _backwardPin;
  uint8_t _forwardPin;
  uint8_t _startStopPin;
  uint8_t _encoderPin;
  uint8_t _backwardSwitchPin;
  uint8_t _forwardSwitchPin;

  static void handleBackwardEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
  static void handleForwardEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
  static void handleStartStopEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
  static void handleEncoderEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
  static void handleBackwardSwitchEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
  static void handleForwardSwitchEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
};
