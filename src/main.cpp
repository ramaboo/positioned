#include <Arduino.h>
#include <FastAccelStepper.h>
#include <ESP32RotaryEncoder.h>
#include <AceButton.h>
using namespace ace_button;

#include "Led.h"
#include "ButtonController.h"
#include "EncoderController.h"



#define dirPinStepper 4
#define enablePinStepper 5
#define stepPinStepper   6

constexpr uint8_t LED_PIN = 38;

constexpr uint8_t ENCODER_CLK_PIN = 15;
constexpr uint8_t ENCODER_DT_PIN = 16;

constexpr uint8_t BUTTON_BACK_PIN = 11;
constexpr uint8_t BUTTON_CONTROL_PIN = 12;
constexpr uint8_t BUTTON_FORWARD_PIN = 13;
constexpr uint8_t BUTTON_ENCODER_PIN = 17;


FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = nullptr;

Led led(LED_PIN);
ButtonController buttonController(BUTTON_BACK_PIN, BUTTON_CONTROL_PIN, BUTTON_FORWARD_PIN, BUTTON_ENCODER_PIN);
EncoderController encoderController(ENCODER_CLK_PIN, ENCODER_DT_PIN);




void setup() {
  Serial.begin(115200);

  led.begin();
  led.setRed();

  engine.init();
   stepper = engine.stepperConnectToPin(stepPinStepper);
   if (stepper) {
      stepper->setDirectionPin(dirPinStepper);
      stepper->setEnablePin(enablePinStepper);
      stepper->setAutoEnable(false);
      stepper->enableOutputs();
      stepper->setAcceleration(1000);
   // run continuously until stopped


      led.setMagenta();
   }

  encoderController.setStepper(stepper);
  encoderController.begin();

  buttonController.setStepper(stepper);
  buttonController.begin();

  led.setGreen();
}




void loop() {
  buttonController.loop();
}



