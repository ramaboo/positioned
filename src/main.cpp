#include <Arduino.h>

#include "App.h"
#include "ButtonController.h"
#include "Config.h"
#include "EncoderController.h"
#include "LedController.h"
#include "StepperController.h"
#include "SwitchController.h"

LedController ledController(LED_PIN);
StepperController stepperController(STEPPER_STEP_PIN, STEPPER_DIR_PIN, STEPPER_ENABLE_PIN);
EncoderController encoderController(ENCODER_CLK_PIN, ENCODER_DT_PIN);
ButtonController buttonController(BUTTON_BACKWARD_PIN, BUTTON_FORWARD_PIN, BUTTON_START_STOP_PIN, BUTTON_ENCODER_PIN);
SwitchController switchController(SWITCH_BACKWARD_PIN, SWITCH_FORWARD_PIN);

static App app(&ledController, &stepperController, &encoderController, &buttonController, &switchController);

void setup() {
  Serial.begin(115200);
  app.begin();
}

void loop() { app.update(); }
