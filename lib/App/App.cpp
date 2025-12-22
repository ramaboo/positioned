#include "App.h"

#include "ButtonController.h"
#include "EncoderController.h"
#include "Event.h"
#include "LedController.h"
#include "StepperController.h"

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
      case EventType::BackwardPressed:
        Serial.println("EV: Backward Pressed");
        handleBackwardPressed();
        break;
      case EventType::BackwardReleased:
        Serial.println("EV: Backward Released");
        handleBackwardReleased();
        break;
      case EventType::ForwardPressed:
        Serial.println("EV: Forward Pressed");
        handleForwardPressed();
        break;
      case EventType::ForwardReleased:
        Serial.println("EV: Forward Released");
        handleForwardReleased();
        break;
      case EventType::StartStopPressed:
        Serial.println("EV: Start Stop Pressed");
        handleStartStopPressed();
        break;
      case EventType::StartStopReleased:
        Serial.println("EV: Start Stop Released");
        handleStartStopReleased();
        break;
      case EventType::EncoderPressed:
        Serial.println("EV: Encoder Pressed");
        handleEncoderPressed();
        break;
      case EventType::EncoderReleased:
        Serial.println("EV: Encoder Released");
        handleEncoderReleased();
        break;
      case EventType::EncoderTurn:
        Serial.println("EV: Encoder Turn " + String(ev.value));
        handleEncoderTurn(ev.value);
        break;
      case EventType::SwitchBackward:
        Serial.println("EV: Switch Backward");
        handleSwitchBackward();
        break;
      case EventType::SwitchForward:
        Serial.println("EV: Switch Forward");
        handleSwitchForward();
        break;
      case EventType::SwitchOff:
        Serial.println("EV: Switch Off");
        handleSwitchOff();
        break;
      default:
        Serial.println("EV: Unknown Event");
        break;
    }
  }

  _buttonController->update();
}
void App::handleBackwardPressed() {
  if (_stepperController) {
    _stepperController->setSpeed(_currentSpeed);
    _stepperController->runBackward();
  }
  if (_ledController) _ledController->setBlue();
  _state = State::Running;
}

void App::handleBackwardReleased() {
  if (_stepperController) _stepperController->stop();
  if (_ledController) _ledController->setBlack();
  _state = State::Idle;
}

void App::handleForwardPressed() {
  if (_stepperController) {
    _stepperController->setSpeed(_currentSpeed);
    _stepperController->runForward();
  }
  if (_ledController) _ledController->setGreen();
  _state = State::Running;
}

void App::handleForwardReleased() {
  if (_stepperController) _stepperController->stop();
  if (_ledController) _ledController->setBlack();
  _state = State::Idle;
}

void App::handleStartStopPressed() {
  if (_stepperController) _stepperController->stop();
  _state = State::Idle;
}

void App::handleStartStopReleased() {}

void App::handleEncoderPressed() {}

void App::handleEncoderReleased() {}

void App::handleEncoderTurn(uint32_t value) {
  _currentSpeed = value * 4;
  if (_stepperController) {
    _stepperController->setSpeed(_currentSpeed);
  }
}

void App::handleSwitchBackward() {
  if (_stepperController) {
    _stepperController->setSpeed(_currentSpeed);
    _stepperController->runBackward();
  }
  if (_ledController) _ledController->setBlue();
  _state = State::Running;
}

void App::handleSwitchForward() {
  if (_stepperController) {
    _stepperController->setSpeed(_currentSpeed);
    _stepperController->runForward();
  }
  if (_ledController) _ledController->setGreen();
  _state = State::Running;
}

void App::handleSwitchOff() {
  if (_stepperController) _stepperController->stop();
  if (_ledController) _ledController->setBlack();
  _state = State::Idle;
}
