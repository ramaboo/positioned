#pragma once
#include <AceButton.h>
using namespace ace_button;

class ButtonController {
 public:
  ButtonController(uint8_t backwardPin, uint8_t forwardPin, uint8_t startStopPin, uint8_t encoderPin);
  void begin();
  void update();

 private:
  AceButton _backwardButton;
  AceButton _forwardButton;
  AceButton _startStopButton;
  AceButton _encoderButton;

  static void handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState);
};
