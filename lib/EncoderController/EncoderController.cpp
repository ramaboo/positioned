#include "EncoderController.h"

#include "Event.h"

static EncoderController* instance = nullptr;

EncoderController::EncoderController(uint8_t clkPin, uint8_t dtPin) : _encoder(clkPin, dtPin) { instance = this; }

void EncoderController::begin() {
  _encoder.setEncoderType(EncoderType::HAS_PULLUP);
  _encoder.setBoundaries(MIN_SPEED, MAX_SPEED, false);
  _encoder.onTurned(&knobCallback);
  _encoder.begin();
}

void EncoderController::knobCallback(int32_t value) {
  if (value == 1) {
    EventQueue::post(Event{EventType::EncoderTurnRight, value});
  } else if (value == -1) {
    EventQueue::post(Event{EventType::EncoderTurnLeft, value});
  }

  if (instance) {
    instance->_encoder.setEncoderValue(0);
  }
}
