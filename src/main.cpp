#include <Arduino.h>

#include "App.h"
#include "LedController.h"
#include "StepperController.h"
#include "EncoderController.h"
#include "ButtonController.h"

constexpr uint8_t LED_PIN = 38;

constexpr uint8_t STEPPER_DIR_PIN = 4;
constexpr uint8_t STEPPER_ENABLE_PIN = 5;
constexpr uint8_t STEPPER_STEP_PIN = 6;

constexpr uint8_t ENCODER_CLK_PIN = 15;
constexpr uint8_t ENCODER_DT_PIN = 16;

constexpr uint8_t BUTTON_BACK_PIN = 11;
constexpr uint8_t BUTTON_CONTROL_PIN = 12;
constexpr uint8_t BUTTON_FORWARD_PIN = 13;
constexpr uint8_t BUTTON_ENCODER_PIN = 17;

LedController ledController(LED_PIN);
StepperController stepperController(STEPPER_STEP_PIN, STEPPER_DIR_PIN, STEPPER_ENABLE_PIN);
EncoderController encoderController(ENCODER_CLK_PIN, ENCODER_DT_PIN);
ButtonController buttonController(BUTTON_BACK_PIN, BUTTON_CONTROL_PIN, BUTTON_FORWARD_PIN, BUTTON_ENCODER_PIN);

static App app(&ledController, &stepperController, &encoderController, &buttonController);

void setup() {
  Serial.begin(115200);
  app.begin();
}

void loop() {
  app.update();
}



