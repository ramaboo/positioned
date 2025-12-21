#include <Arduino.h>
#include "ButtonController.h"
#include "Event.h"

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

void ButtonController::update() {
  _backButton.check();
  _controlButton.check();
  _forwardButton.check();
  _encoderButton.check();
}

void ButtonController::handleBackEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Back: Pressed");
      EventQueue::post(Event{EventType::BackPressed, 0});
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Back: Released");
      EventQueue::post(Event{EventType::BackReleased, 0});
      break;
  }
}

void ButtonController::handleControlEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Control: Pressed");
      EventQueue::post(Event{EventType::ControlPressed, 0});
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Control: Released");
      EventQueue::post(Event{EventType::ControlReleased, 0});
      break;
  }
}

void ButtonController::handleForwardEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Forward: Pressed");
      EventQueue::post(Event{EventType::ForwardPressed, 0});
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Forward: Released");
      EventQueue::post(Event{EventType::ForwardReleased, 0});
      break;
  }
}

void ButtonController::handleEncoderEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button Encoder: Pressed");
      EventQueue::post(Event{EventType::EncoderPressed, 0});
      break;
    case AceButton::kEventReleased:
      Serial.println("Button Encoder: Released");
      EventQueue::post(Event{EventType::EncoderReleased, 0});
      break;
  }
}
