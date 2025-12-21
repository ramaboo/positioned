#include <Arduino.h>

#include "EncoderController.h"
#include "Event.h"

constexpr uint32_t MAX_SPEED = 1000;
constexpr uint32_t MIN_SPEED = 0;

EncoderController::EncoderController(uint8_t clkPin, uint8_t dtPin)
  : _encoder(clkPin, dtPin) {}

void EncoderController::begin() {
  _encoder.setEncoderType(EncoderType::HAS_PULLUP);
  _encoder.setBoundaries(MIN_SPEED, MAX_SPEED, false);
  _encoder.onTurned(&knobCallback);
  _encoder.begin();
}

void EncoderController::knobCallback(uint32_t value) {
  EventQueue::post(Event{EventType::EncoderTurn, value});
}
