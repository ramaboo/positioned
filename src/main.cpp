#include <Arduino.h>


#include <LED.h>




void setup() {
  Serial.begin(115200);
  // Initialize LED (uses LED_BUILTIN by default). If your board's
  // onboard LED is active-low, pass `true` as second argument.



  setupLed();

  ledRed();

}

void loop() {
  Serial.println("test");
  delay(10);
}
