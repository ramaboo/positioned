#include "App.h"

#include "ButtonController.h"
#include "EncoderController.h"
#include "Event.h"
#include "LedController.h"
#include "StepperController.h"

App::App(LedController* ledController, StepperController* stepperController, EncoderController* encoderController, ButtonController* buttonController)
    : _ledController(ledController), _stepperController(stepperController), _encoderController(encoderController), _buttonController(buttonController) {}

void App::begin() {
  validate();

  _ledController->begin();
  _stepperController->begin();
  _encoderController->begin();
  _buttonController->begin();

  _ledController->setWhite();
}

void App::update() {
  Event ev;
  while (EventQueue::poll(ev)) {
    switch (ev.type) {
      case EventType::None:
        Serial.println("EV: None");
        break;
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
      case EventType::EncoderTurnRight:
        Serial.println("EV: Encoder Turn Right");
        handleEncoderTurnRight(ev.value);
        break;
      case EventType::EncoderTurnLeft:
        Serial.println("EV: Encoder Turn Left");
        handleEncoderTurnLeft(ev.value);
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
  _stepperController->setSpeed(_userSpeed);
  _stepperController->runBackward();
  _ledController->setMagenta();

  _currentDirection = Direction::Backward;
}

void App::handleBackwardReleased() {
  _stepperController->stop();
  _ledController->setBlack();

  _currentDirection = Direction::Off;
}

void App::handleForwardPressed() {
  _stepperController->setSpeed(_userSpeed);
  _stepperController->runForward();
  _ledController->setCyan();

  _currentDirection = Direction::Forward;
}

void App::handleForwardReleased() {
  _stepperController->stop();
  _ledController->setBlack();

  _currentDirection = Direction::Off;
}

void App::handleStartStopPressed() {
  if (_currentDirection == Direction::Off) {
    if (_userDirection == Direction::Forward) {
      _stepperController->setSpeed(_userSpeed);
      _stepperController->runForward();
      _ledController->setCyan();
      _currentDirection = Direction::Forward;
    } else if (_userDirection == Direction::Backward) {
      _stepperController->setSpeed(_userSpeed);
      _stepperController->runBackward();
      _ledController->setMagenta();
      _currentDirection = Direction::Backward;
    }
  } else {
    _stepperController->stop();
    _ledController->setBlack();
    _currentDirection = Direction::Off;
  }
}

void App::handleStartStopReleased() { /* Do nothing. */ }

void App::handleEncoderPressed() {
  if (_userEncoderSpeed == EncoderSpeed::Slow) {
    _userEncoderSpeed = EncoderSpeed::Fast;
    _ledController->setBlue();
  } else {
    _userEncoderSpeed = EncoderSpeed::Slow;
    _ledController->setYellow();
  }
}

void App::handleEncoderReleased() { /* Do nothing. */ }

void App::handleEncoderTurnRight(int32_t value) {
  updateUserSpeed(value);
  _ledController->setGreen();
}

void App::handleEncoderTurnLeft(int32_t value) {
  updateUserSpeed(value);
  _ledController->setRed();
}

void App::handleSwitchBackward() { _userDirection = Direction::Backward; }

void App::handleSwitchForward() { _userDirection = Direction::Forward; }

void App::handleSwitchOff() {
  _userDirection = Direction::Off;
  _stepperController->stop();
  _ledController->setBlack();

  _userDirection = Direction::Off;
  _currentDirection = Direction::Off;
}

void App::validate() {
  if (!_ledController || !_stepperController || !_encoderController || !_buttonController) {
    if (!_ledController) {
      Serial.println("App: LED Failed");
    }

    if (!_stepperController) {
      Serial.println("App: Stepper Failed");
    }

    if (!_encoderController) {
      Serial.println("App: Encoder Failed");
    }

    if (!_buttonController) {
      Serial.println("App: Button Failed");
    }

    Serial.println("App: Restarting");

    delay(5000);
    ESP.restart();
  }
}

void App::updateUserSpeed(int32_t value) {
  int32_t step = 0;

  if (_userEncoderSpeed == EncoderSpeed::Slow) {
    step = SLOW_SPEED_STEP * value;
  } else if (_userEncoderSpeed == EncoderSpeed::Fast) {
    step = FAST_SPEED_STEP * value;
  }

  _userSpeed += step;

  if (_userSpeed < 0) {
    _userSpeed = 0;
  } else if (_userSpeed > MAX_USER_SPEED) {
    _userSpeed = MAX_USER_SPEED;
  }

  Serial.println("User Speed: " + String(_userSpeed));
  _stepperController->setSpeed(_userSpeed);
}
