#include <Arduino.h>
#include <FastAccelStepper.h>

#include "EncoderController.h"

constexpr uint32_t MAX_SPEED = 1000;
constexpr uint32_t MIN_SPEED = 0;
constexpr uint32_t SPEED_MULTIPLE = 4;

FastAccelStepper* EncoderController::s_stepper = nullptr;

EncoderController::EncoderController(uint8_t clkPin, uint8_t dtPin)
  : _encoder(clkPin, dtPin) {}

void EncoderController::begin() {
  _encoder.setEncoderType(EncoderType::HAS_PULLUP);
  _encoder.setBoundaries(MIN_SPEED, MAX_SPEED, false);
  _encoder.onTurned(&knobCallback);
  _encoder.begin();
}

void EncoderController::setStepper(FastAccelStepper* stepper) { s_stepper = stepper; }

void EncoderController::knobCallback(uint32_t value) {
  Serial.println("Encoder: " + String(value));

  uint32_t speed = value * SPEED_MULTIPLE;

  s_stepper->setSpeedInHz(speed);
  s_stepper->runBackward();
}
