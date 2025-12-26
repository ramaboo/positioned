#include "SwitchController.h"

#include "Event.h"

SwitchController::SwitchController(uint8_t backwardPin, uint8_t forwardPin) : _backwardPin(backwardPin), _forwardPin(forwardPin) {}

void SwitchController::begin() {
  pinMode(_backwardPin, INPUT_PULLUP);
  pinMode(_forwardPin, INPUT_PULLUP);
}

void SwitchController::update() {
  Direction direction = getDirection();
  const uint32_t now = millis();
  const uint32_t ago = now - _lastChangeAtMs;

  if ((direction != _lastDirection) && (ago >= DEBOUNCE_MS)) {
    _lastDirection = direction;
    _lastChangeAtMs = now;

    switch (direction) {
      case Direction::Off:
        EventQueue::post(Event{EventType::SwitchOff, 0});
        break;
      case Direction::Forward:
        EventQueue::post(Event{EventType::SwitchForward, 0});
        break;
      case Direction::Backward:
        EventQueue::post(Event{EventType::SwitchBackward, 0});
        break;
    }
  }
}

Direction SwitchController::getDirection() {
  bool backwardState = digitalRead(_backwardPin) == LOW;
  bool forwardState = digitalRead(_forwardPin) == LOW;

  if (backwardState) {
    return Direction::Backward;
  } else if (forwardState) {
    return Direction::Forward;
  } else {
    return Direction::Off;
  }
}
