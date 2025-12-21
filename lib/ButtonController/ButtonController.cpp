#include <Arduino.h>
#include <FastAccelStepper.h>
#include "ButtonController.h"

FastAccelStepper* ButtonController::s_stepper = nullptr;

ButtonController::ButtonController(uint8_t backPin, uint8_t controlPin, uint8_t forwardPin, uint8_t encoderPin)
  : _backPin(backPin), _backButton(&_backConfig), _controlPin(controlPin), _controlButton(&_controlConfig), _forwardPin(forwardPin), _forwardButton(&_forwardConfig), _encoderPin(encoderPin), _encoderButton(&_encoderConfig) {}

void ButtonController::begin() {
  pinMode(_backPin, INPUT_PULLUP);
  pinMode(_controlPin, INPUT_PULLUP);
  pinMode(_forwardPin, INPUT_PULLUP);
  pinMode(_encoderPin, INPUT_PULLUP);

  _backConfig.setEventHandler(handleBackEvent);
  _backButton.init(_backPin);

  _controlConfig.setEventHandler(handleControlEvent);
  _controlButton.init(_controlPin);

  _forwardConfig.setEventHandler(handleForwardEvent);
  _forwardButton.init(_forwardPin);

  _encoderConfig.setEventHandler(handleEncoderEvent);
  _encoderButton.init(_encoderPin);
}

void ButtonController::loop() {
  _backButton.check();
  _controlButton.check();
  _forwardButton.check();
  _encoderButton.check();
}

void ButtonController::setStepper(FastAccelStepper* stepper) { s_stepper = stepper; }

void ButtonController::handleBackEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  if (s_stepper == nullptr) return;
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Back: Pressed");
      s_stepper->runBackward();
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Back: Released");
      s_stepper->stopMove();
      break;
  }
}

void ButtonController::handleControlEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  if (s_stepper == nullptr) return;

  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Control: Pressed");
      s_stepper->stopMove();
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Control: Released");
      break;
  }
}

void ButtonController::handleForwardEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {

  if (s_stepper == nullptr) return;

  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Forward: Pressed");
      s_stepper->runForward();
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Forward: Released");
      s_stepper->stopMove();
      break;
  }
}

void ButtonController::handleEncoderEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Encoder: Pressed");
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Encoder: Released");
      break;
  }
}
