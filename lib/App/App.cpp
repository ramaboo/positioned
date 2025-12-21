#include "App.h"
#include <Arduino.h>
#include "LedController.h"
#include "StepperController.h"
#include "EncoderController.h"
#include "ButtonController.h"
#include "Event.h"

App::App(LedController* ledController, StepperController* stepperController, EncoderController* encoderController, ButtonController* buttonController)
  : _ledController(ledController), _stepperController(stepperController), _encoderController(encoderController), _buttonController(buttonController) {}

void App::begin() {
  if (_ledController) _ledController->begin();
  if (_stepperController) _stepperController->begin();
  if (_encoderController) _encoderController->begin();
  if (_buttonController) _buttonController->begin();
}

void App::update() {
  Event ev;
  while (EventQueue::poll(ev)) {
    switch (ev.type) {
      case EventType::BackPressed:
        handleBackPressed();
        break;
      case EventType::BackReleased:
        handleBackReleased();
        break;
      case EventType::ForwardPressed:
        handleForwardPressed();
        break;
      case EventType::ForwardReleased:
        handleForwardReleased();
        break;
      case EventType::ControlPressed:
        handleControlPressed();
        break;
      case EventType::ControlReleased:
        handleControlReleased();
        break;
      case EventType::EncoderPressed:
        handleEncoderPressed();
        break;
      case EventType::EncoderReleased:
        handleEncoderReleased();
        break;
      case EventType::EncoderTurn:
        handleEncoderTurn(ev.value);
        break;
      default:
        break;
    }
  }

  _buttonController->update();
}

void App::onBackPressed() { EventQueue::post(Event{EventType::BackPressed, 0}); }
void App::onBackReleased() { EventQueue::post(Event{EventType::BackReleased, 0}); }
void App::onControlPressed() { EventQueue::post(Event{EventType::ControlPressed, 0}); }
void App::onControlReleased() { EventQueue::post(Event{EventType::ControlReleased, 0}); }
void App::onForwardPressed() { EventQueue::post(Event{EventType::ForwardPressed, 0}); }
void App::onForwardReleased() { EventQueue::post(Event{EventType::ForwardReleased, 0}); }
void App::onEncoderPressed() { EventQueue::post(Event{EventType::EncoderPressed, 0}); }
void App::onEncoderReleased() { EventQueue::post(Event{EventType::EncoderReleased, 0}); }
void App::onEncoderTurn(uint32_t value) { EventQueue::post(Event{EventType::EncoderTurn, value}); }

void App::handleBackPressed() {
  Serial.println("EV: BackPressed");
  if (StepperController::getStepper()) StepperController::getStepper()->runBackward();
  if (_ledController) _ledController->setBlue();
  _state = State::Running;
}

void App::handleBackReleased() {
  Serial.println("EV: BackReleased");
  if (StepperController::getStepper()) StepperController::getStepper()->stopMove();
  if (_ledController) _ledController->setBlack();
  _state = State::Idle;
}

void App::handleControlPressed() {
  Serial.println("EV: ControlPressed");
  if (StepperController::getStepper()) StepperController::getStepper()->stopMove();
  _state = State::Idle;
}

void App::handleControlReleased() {
  Serial.println("EV: ControlReleased");
}

void App::handleForwardPressed() {
  Serial.println("EV: ForwardPressed");
  if (StepperController::getStepper()) StepperController::getStepper()->runForward();
  if (_ledController) _ledController->setGreen();
  _state = State::Running;
}

void App::handleForwardReleased() {
  Serial.println("EV: ForwardReleased");
  if (StepperController::getStepper()) StepperController::getStepper()->stopMove();
  if (_ledController) _ledController->setBlack();
  _state = State::Idle;
}

void App::handleEncoderPressed() {
  Serial.println("EV: EncoderPressed");
}

void App::handleEncoderReleased() {
  Serial.println("EV: EncoderReleased");
}

void App::handleEncoderTurn(uint32_t value) {
  Serial.println("EV: EncoderTurn " + String(value));
  if (StepperController::getStepper()) {
    StepperController::getStepper()->setSpeedInHz(value * 4);
    StepperController::getStepper()->runBackward();
    _state = State::Running;
  }
}
