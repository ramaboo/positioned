#include <Adafruit_NeoPixel.h>
#include "Led.h"

Led::Led(uint8_t pin)
  : _pin(pin), _strip(1, _pin, NEO_GRB + NEO_KHZ800) {}

void Led::begin() {
  _strip.setBrightness(127);
  _strip.begin();
  _strip.show();
}

void Led::setColor(uint8_t red, uint8_t green, uint8_t blue) {
  _strip.setPixelColor(0, _strip.Color(red, green, blue));
  _strip.show();
}

void Led::setBrightness(uint8_t brightness) {
  _strip.setBrightness(brightness);
  _strip.show();
}

void Led::on() {
  setWhite();
}

void Led::off() {
  setBlack();
}

void Led::setRed() {
  setColor(255, 0, 0);
}

void Led::setGreen() {
  setColor(0, 255, 0);
}

void Led::setBlue() {
  setColor(0, 0, 255);
}

void Led::setCyan() {
  setColor(0, 255, 255);
}

void Led::setMagenta() {
  setColor(255, 0, 255);
}

void Led::setYellow() {
  setColor(255, 255, 0);
}

void Led::setWhite() {
  setColor(255, 255, 255);
}

void Led::setBlack() {
  setColor(0, 0, 0);
}
