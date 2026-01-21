#include "App.h"

#include "ButtonController.h"
#include "EncoderController.h"
#include "Event.h"
#include "LedController.h"
#include "StepperController.h"

App::App(ButtonController* buttonController, EncoderController* encoderController, LedController* ledController, StepperController* stepperController,
         SwitchController* switchController)
    : _buttonController(buttonController),
      _encoderController(encoderController),
      _ledController(ledController),
      _stepperController(stepperController),
      _switchController(switchController) {}

void App::begin() {
  Serial.println("App: Initializing");

  validate();

  _buttonController->begin();
  _encoderController->begin();
  _ledController->begin();
  _stepperController->begin();
  _switchController->begin();

  Serial.println("App: Started");

  _ledController->setWhite();
}

void App::update() {
  _buttonController->update();
  _switchController->update();

  processEvents();
}

void App::handleBackwardPressed() {
  _stepperController->setSpeed(_userSpeed);
  _stepperController->runBackward();
  _currentDirection = Direction::Backward;

  _ledController->setMagenta();
}

void App::handleBackwardReleased() {
  _stepperController->stop();
  _currentDirection = Direction::Off;

  _ledController->setBlack();
}

void App::handleForwardPressed() {
  _stepperController->setSpeed(_userSpeed);
  _stepperController->runForward();
  _currentDirection = Direction::Forward;

  _ledController->setCyan();
}

void App::handleForwardReleased() {
  _stepperController->stop();
  _currentDirection = Direction::Off;

  _ledController->setBlack();
}

void App::handleStartStopPressed() {
  if (_currentDirection == Direction::Off) {
    if (_userDirection == Direction::Forward) {
      _stepperController->setSpeed(_userSpeed);
      _stepperController->runForward();
      _currentDirection = Direction::Forward;

      _ledController->setCyan();
    } else if (_userDirection == Direction::Backward) {
      _stepperController->setSpeed(_userSpeed);
      _stepperController->runBackward();
      _currentDirection = Direction::Backward;

      _ledController->setMagenta();
    }
  } else {
    _stepperController->stop();
    _currentDirection = Direction::Off;

    _ledController->setBlack();
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

void App::handleSwitchOff() {
  _stepperController->stop();
  _userDirection = Direction::Off;
  _currentDirection = Direction::Off;

  _ledController->setBlack();
}

void App::handleSwitchForward() { _userDirection = Direction::Forward; }

void App::handleSwitchBackward() { _userDirection = Direction::Backward; }

void App::validate() {
  if (!_ledController || !_stepperController || !_encoderController || !_buttonController || !_switchController) {
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

    if (!_switchController) {
      Serial.println("App: Switch Failed");
    }

    Serial.println("App: Restarting");

    if (_ledController) {
      _ledController->setRed();
    }

    delay(5000);
    ESP.restart();
  }
}

void App::updateUserSpeed(int32_t value) {
  const int32_t step = value * ((_userEncoderSpeed == EncoderSpeed::Slow) ? SLOW_SPEED_STEP : FAST_SPEED_STEP);

  _userSpeed += step;

  _userSpeed = constrain(_userSpeed, MIN_USER_SPEED, MAX_USER_SPEED);

  Serial.println("App: Speed " + String(_userSpeed));
  _stepperController->setSpeed(_userSpeed);
}

void App::processEvents() {
  Event event;
  while (EventQueue::poll(event)) {
    switch (event.type) {
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
        handleEncoderTurnRight(event.value);
        break;
      case EventType::EncoderTurnLeft:
        Serial.println("EV: Encoder Turn Left");
        handleEncoderTurnLeft(event.value);
        break;
      case EventType::SwitchOff:
        Serial.println("EV: Switch Off");
        handleSwitchOff();
        break;
      case EventType::SwitchForward:
        Serial.println("EV: Switch Forward");
        handleSwitchForward();
        break;
      case EventType::SwitchBackward:
        Serial.println("EV: Switch Backward");
        handleSwitchBackward();
        break;
      default:
        Serial.println("EV: Unknown Event");
        break;
    }
  }
}
