#include <Arduino.h>

#include "App.h"
#include "ButtonController.h"
#include "EncoderController.h"
#include "LedController.h"
#include "StepperController.h"

constexpr uint8_t LED_PIN = 38;

constexpr uint8_t STEPPER_DIR_PIN = 4;
constexpr uint8_t STEPPER_ENABLE_PIN = 5;
constexpr uint8_t STEPPER_STEP_PIN = 6;

constexpr uint8_t ENCODER_CLK_PIN = 15;
constexpr uint8_t ENCODER_DT_PIN = 16;

constexpr uint8_t BUTTON_BACKWARD_PIN = 11;
constexpr uint8_t BUTTON_FORWARD_PIN = 13;
constexpr uint8_t BUTTON_START_STOP_PIN = 12;
constexpr uint8_t BUTTON_ENCODER_PIN = 17;

constexpr uint8_t SWITCH_BACKWARD_PIN = 37;
constexpr uint8_t SWITCH_FORWARD_PIN = 19;

LedController ledController(LED_PIN);
StepperController stepperController(STEPPER_STEP_PIN, STEPPER_DIR_PIN, STEPPER_ENABLE_PIN);
EncoderController encoderController(ENCODER_CLK_PIN, ENCODER_DT_PIN);
ButtonController buttonController(BUTTON_BACKWARD_PIN, BUTTON_FORWARD_PIN, BUTTON_START_STOP_PIN, BUTTON_ENCODER_PIN, SWITCH_BACKWARD_PIN, SWITCH_FORWARD_PIN);

static App app(&ledController, &stepperController, &encoderController, &buttonController);

void setup() {
  Serial.begin(115200);
  app.begin();
}

void loop() { app.update(); }
