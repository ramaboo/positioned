#include "StepperController.h"

static FastAccelStepperEngine engine = FastAccelStepperEngine();

FastAccelStepper* StepperController::s_stepper = nullptr;

StepperController::StepperController(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin) : _stepPin(stepPin), _dirPin(dirPin), _enablePin(enablePin) {}

void StepperController::begin() {
  engine.init();
  s_stepper = engine.stepperConnectToPin(_stepPin);

  validate();

  s_stepper->setDirectionPin(_dirPin);
  s_stepper->setEnablePin(_enablePin);
  s_stepper->setAutoEnable(false);
  s_stepper->enableOutputs();
  s_stepper->setAcceleration(ACCELERATION);

  stop();
}

void StepperController::setSpeed(int32_t speed) {
  s_stepper->setSpeedInHz(speed);

  if (s_stepper->isRunning()) {
    s_stepper->applySpeedAcceleration();
  }
}

void StepperController::runForward() { s_stepper->runForward(); }

void StepperController::runBackward() { s_stepper->runBackward(); }

void StepperController::stop() { s_stepper->stopMove(); }

bool StepperController::isRunning() { return s_stepper->isRunning(); }

Direction StepperController::getDirection() {
  uint8_t state = s_stepper->rampState();

  if (state & RAMP_DIRECTION_COUNT_UP) {
    return Direction::Forward;
  } else if (state & RAMP_DIRECTION_COUNT_DOWN) {
    return Direction::Backward;
  }

  return Direction::Off;
}

void StepperController::validate() {
  if (!s_stepper) {
    Serial.println("Stepper: Initalization Failed");

    delay(5000);
    ESP.restart();
  }
}
