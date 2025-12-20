#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 38

Adafruit_NeoPixel pixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupLed() {
  pixel.begin();
  pixel.show();
  pixel.setBrightness(50);
}

void ledRed() {
  Serial.println("LED: Red");
  pixel.setPixelColor(0, pixel.Color(127, 0, 0));
  pixel.show();
}

void ledGreen() {
  Serial.println("LED: Green");
}
void ledBlue() {
  Serial.println("LED: Blue");
}
