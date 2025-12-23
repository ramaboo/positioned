#include "ButtonController.h"

#include <Arduino.h>

#include "Config.h"
#include "Event.h"

ButtonController::ButtonController(uint8_t backwardPin, uint8_t forwardPin, uint8_t startStopPin, uint8_t encoderPin, uint8_t backwardSwitchPin,
                                   uint8_t forwardSwitchPin)
    : _backwardButton(backwardPin),
      _forwardButton(forwardPin),
      _startStopButton(startStopPin),
      _encoderButton(encoderPin),
      _backwardSwitch(backwardSwitchPin),
      _forwardSwitch(forwardSwitchPin) {}

void ButtonController::begin() {
  pinMode(_backwardButton.getPin(), INPUT_PULLUP);
  pinMode(_forwardButton.getPin(), INPUT_PULLUP);
  pinMode(_startStopButton.getPin(), INPUT_PULLUP);
  pinMode(_encoderButton.getPin(), INPUT_PULLUP);
  pinMode(_backwardSwitch.getPin(), INPUT_PULLUP);
  pinMode(_forwardSwitch.getPin(), INPUT_PULLUP);

  ButtonConfig* buttonConfig = ButtonConfig::getSystemButtonConfig();
  buttonConfig->setEventHandler(handleEvent);

  // Send initial events for current switch positions.
  if (digitalRead(_backwardSwitch.getPin()) == LOW) {
    EventQueue::post(Event{EventType::SwitchBackward, 0});
  } else if (digitalRead(_forwardSwitch.getPin()) == LOW) {
    EventQueue::post(Event{EventType::SwitchForward, 0});
  } else {
    EventQueue::post(Event{EventType::SwitchOff, 0});
  }
}

void ButtonController::update() {
  _backwardButton.check();
  _forwardButton.check();
  _startStopButton.check();
  _encoderButton.check();
  _backwardSwitch.check();
  _forwardSwitch.check();
}

void ButtonController::handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      switch (button->getPin()) {
        case BUTTON_BACKWARD_PIN:
          EventQueue::post(Event{EventType::BackwardPressed, 0});
          break;
        case BUTTON_FORWARD_PIN:
          EventQueue::post(Event{EventType::ForwardPressed, 0});
          break;
        case BUTTON_START_STOP_PIN:
          EventQueue::post(Event{EventType::StartStopPressed, 0});
          break;
        case BUTTON_ENCODER_PIN:
          EventQueue::post(Event{EventType::EncoderPressed, 0});
          break;
        case SWITCH_BACKWARD_PIN:
          EventQueue::post(Event{EventType::SwitchBackward, 0});
          break;
        case SWITCH_FORWARD_PIN:
          EventQueue::post(Event{EventType::SwitchForward, 0});
          break;
      }
      break;
    case AceButton::kEventReleased:
      switch (button->getPin()) {
        case BUTTON_BACKWARD_PIN:
          EventQueue::post(Event{EventType::BackwardReleased, 0});
          break;
        case BUTTON_FORWARD_PIN:
          EventQueue::post(Event{EventType::ForwardReleased, 0});
          break;
        case BUTTON_START_STOP_PIN:
          EventQueue::post(Event{EventType::StartStopReleased, 0});
          break;
        case BUTTON_ENCODER_PIN:
          EventQueue::post(Event{EventType::EncoderReleased, 0});
          break;
        case SWITCH_BACKWARD_PIN:
          EventQueue::post(Event{EventType::SwitchOff, 0});
          break;
        case SWITCH_FORWARD_PIN:
          EventQueue::post(Event{EventType::SwitchOff, 0});
          break;
      }
      break;
  }
}
