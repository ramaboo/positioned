#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Led {
public:
  explicit Led(uint8_t pin);

  void begin();

  void setColor(uint8_t red, uint8_t green, uint8_t blue);
  void setBrightness(uint8_t brightness);

  void on();
  void off();

  void setRed();
  void setGreen();
  void setBlue();
  void setCyan();
  void setMagenta();
  void setYellow();
  void setWhite();
  void setBlack();

private:
  uint8_t _pin;
  Adafruit_NeoPixel _strip;
};
