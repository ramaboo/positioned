#pragma once
#include <AceButton.h>
using namespace ace_button;

class ButtonController {
 public:
  ButtonController(uint8_t backwardPin, uint8_t forwardPin, uint8_t startStopPin, uint8_t encoderPin, uint8_t backwardSwitchPin, uint8_t forwardSwitchPin);
  void begin();
  void update();

 private:
  AceButton _backwardButton;
  AceButton _forwardButton;
  AceButton _startStopButton;
  AceButton _encoderButton;
  AceButton _backwardSwitch;
  AceButton _forwardSwitch;

  static void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
};
