#include "ButtonController.h"

#include <Arduino.h>

#include "Event.h"

ButtonController::ButtonController(uint8_t backwardPin, uint8_t forwardPin, uint8_t startStopPin, uint8_t encoderPin, uint8_t backwardSwitchPin,
                                   uint8_t forwardSwitchPin)
    : _backwardPin(backwardPin),
      _backwardButton(&_backwardConfig),
      _forwardPin(forwardPin),
      _forwardButton(&_forwardConfig),
      _startStopPin(startStopPin),
      _startStopButton(&_startStopConfig),
      _encoderPin(encoderPin),
      _encoderButton(&_encoderConfig),
      _backwardSwitchPin(backwardSwitchPin),
      _backwardSwitch(&_backwardSwitchConfig),
      _forwardSwitchPin(forwardSwitchPin),
      _forwardSwitch(&_forwardSwitchConfig) {}

void ButtonController::begin() {
  pinMode(_backwardPin, INPUT_PULLUP);
  pinMode(_forwardPin, INPUT_PULLUP);
  pinMode(_startStopPin, INPUT_PULLUP);
  pinMode(_encoderPin, INPUT_PULLUP);
  pinMode(_backwardSwitchPin, INPUT_PULLUP);
  pinMode(_forwardSwitchPin, INPUT_PULLUP);

  _backwardConfig.setEventHandler(handleBackwardEvent);
  _backwardButton.init(_backwardPin);

  _forwardConfig.setEventHandler(handleForwardEvent);
  _forwardButton.init(_forwardPin);

  _startStopConfig.setEventHandler(handleStartStopEvent);
  _startStopButton.init(_startStopPin);

  _encoderConfig.setEventHandler(handleEncoderEvent);
  _encoderButton.init(_encoderPin);

  _backwardSwitchConfig.setEventHandler(handleBackwardSwitchEvent);
  _backwardSwitch.init(_backwardSwitchPin);

  _forwardSwitchConfig.setEventHandler(handleForwardSwitchEvent);
  _forwardSwitch.init(_forwardSwitchPin);
}

void ButtonController::update() {
  _backwardButton.check();
  _forwardButton.check();
  _startStopButton.check();
  _encoderButton.check();
  _backwardSwitch.check();
  _forwardSwitch.check();
}

void ButtonController::handleBackwardEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      EventQueue::post(Event{EventType::BackwardPressed, 0});
      break;
    case AceButton::kEventReleased:
      EventQueue::post(Event{EventType::BackwardReleased, 0});
      break;
  }
}

void ButtonController::handleForwardEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      EventQueue::post(Event{EventType::ForwardPressed, 0});
      break;
    case AceButton::kEventReleased:
      EventQueue::post(Event{EventType::ForwardReleased, 0});
      break;
  }
}

void ButtonController::handleStartStopEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      EventQueue::post(Event{EventType::StartStopPressed, 0});
      break;
    case AceButton::kEventReleased:
      EventQueue::post(Event{EventType::StartStopReleased, 0});
      break;
  }
}

void ButtonController::handleEncoderEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      EventQueue::post(Event{EventType::EncoderPressed, 0});
      break;
    case AceButton::kEventReleased:
      EventQueue::post(Event{EventType::EncoderReleased, 0});
      break;
  }
}

void ButtonController::handleBackwardSwitchEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      EventQueue::post(Event{EventType::SwitchBackward, 0});
      break;
    case AceButton::kEventReleased:
      EventQueue::post(Event{EventType::SwitchOff, 0});
      break;
  }
}

void ButtonController::handleForwardSwitchEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      EventQueue::post(Event{EventType::SwitchForward, 0});
      break;
    case AceButton::kEventReleased:
      EventQueue::post(Event{EventType::SwitchOff, 0});
      break;
  }
}
