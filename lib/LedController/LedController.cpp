#include <Adafruit_NeoPixel.h>
#include "LedController.h"

LedController::LedController(uint8_t pin)
  : _pin(pin), _strip(1, _pin, NEO_GRB + NEO_KHZ800) {}

void LedController::begin() {
  _strip.setBrightness(127);
  _strip.begin();
  _strip.show();
}

void LedController::setColor(uint8_t red, uint8_t green, uint8_t blue) {
  _strip.setPixelColor(0, _strip.Color(red, green, blue));
  _strip.show();
}

void LedController::setBrightness(uint8_t brightness) {
  _strip.setBrightness(brightness);
  _strip.show();
}

void LedController::on() {
  setWhite();
}

void LedController::off() {
  setBlack();
}

void LedController::setRed() {
  setColor(255, 0, 0);
}

void LedController::setGreen() {
  setColor(0, 255, 0);
}

void LedController::setBlue() {
  setColor(0, 0, 255);
}

void LedController::setCyan() {
  setColor(0, 255, 255);
}

void LedController::setMagenta() {
  setColor(255, 0, 255);
}

void LedController::setYellow() {
  setColor(255, 255, 0);
}

void LedController::setWhite() {
  setColor(255, 255, 255);
}

void LedController::setBlack() {
  setColor(0, 0, 0);
}
