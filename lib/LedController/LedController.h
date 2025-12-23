#pragma once
#include <Adafruit_NeoPixel.h>

class LedController {
 public:
  explicit LedController(uint8_t pin);

  static constexpr uint8_t BRIGHTNESS = 127;

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
