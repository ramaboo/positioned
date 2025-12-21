#include <Arduino.h>
#include "ButtonController.h"
#include "App.h"

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

void ButtonController::handleBackEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Back: Pressed");
      App::get().onBackPressed();
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Back: Released");
      App::get().onBackReleased();
      break;
  }
}

void ButtonController::handleControlEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Control: Pressed");
      App::get().onControlPressed();
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Control: Released");
      App::get().onControlReleased();
      break;
  }
}

void ButtonController::handleForwardEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Forward: Pressed");
      App::get().onForwardPressed();
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Forward: Released");
      App::get().onForwardReleased();
      break;
  }
}

void ButtonController::handleEncoderEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Encoder: Pressed");
      App::get().onEncoderPressed();
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Encoder: Released");
      App::get().onEncoderReleased();
      break;
  }
}
