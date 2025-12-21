#include "App.h"
#include <Arduino.h>
#include "LedController.h"
#include "StepperController.h"
#include "EncoderController.h"
#include "ButtonController.h"

static App* s_app = nullptr;

LedController* App::s_ledController = nullptr;
StepperController* App::s_stepperController = nullptr;
EncoderController* App::s_encoderController = nullptr;
ButtonController* App::s_buttonController = nullptr;

void App::init() {
  if (s_app == nullptr) {
    s_app = new App();
  }

  s_ledController->begin();
  s_stepperController->begin();
  s_encoderController->begin();
  s_buttonController->begin();
}

void App::loop() {
  s_buttonController->loop();
}

void App::setLedController(LedController* ledController) { s_ledController = ledController; }
void App::setStepperController(StepperController* stepperController) { s_stepperController = stepperController; }
void App::setEncoderController(EncoderController* encoderController) { s_encoderController = encoderController; }
void App::setButtonController(ButtonController* buttonController) { s_buttonController = buttonController; }

App& App::get() {
  return *s_app;
}

void App::onBackPressed() {
  Serial.println("App: Back Pressed");
  auto st = StepperController::getStepper();
  if (st) st->runBackward();
  if (s_ledController) s_ledController->setBlue();
}

void App::onBackReleased() {
  Serial.println("App: Back Released");
  auto st = StepperController::getStepper();
  if (st) st->stopMove();
  if (s_ledController) s_ledController->setBlack();
}

void App::onControlPressed() {
  Serial.println("App: Control Pressed");
  auto st = StepperController::getStepper();
  if (st) st->stopMove();
}

void App::onControlReleased() {
  Serial.println("App: Control Released");
}

void App::onForwardPressed() {
  Serial.println("App: Forward Pressed");
  auto st = StepperController::getStepper();
  if (st) st->runForward();
  if (s_ledController) s_ledController->setGreen();
}

void App::onForwardReleased() {
  Serial.println("App: Forward Released");
  auto st = StepperController::getStepper();
  if (st) st->stopMove();
  if (s_ledController) s_ledController->setBlack();
}

void App::onEncoderPressed() {
  Serial.println("App: Encoder Pressed");
}

void App::onEncoderReleased() {
  Serial.println("App: Encoder Released");
}

void App::onEncoderTurn(uint32_t value) {
  Serial.println("App: Encoder Turn " + String(value));
  uint32_t speed = value * 4;
  auto st = StepperController::getStepper();
  if (st) {
    st->setSpeedInHz(speed);
    st->runBackward();
  }
}
