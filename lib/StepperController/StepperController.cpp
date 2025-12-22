#include "StepperController.h"

static FastAccelStepperEngine engine = FastAccelStepperEngine();

FastAccelStepper* StepperController::s_stepper = nullptr;

StepperController::StepperController(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin) : _stepPin(stepPin), _dirPin(dirPin), _enablePin(enablePin) {}

void StepperController::begin() {
  engine.init();
  s_stepper = engine.stepperConnectToPin(_stepPin);

  if (s_stepper) {
    s_stepper->setDirectionPin(_dirPin);
    s_stepper->setEnablePin(_enablePin);
    s_stepper->setAutoEnable(false);
    s_stepper->enableOutputs();
    s_stepper->setAcceleration(1000);

    Serial.println("Stepper: Initialized");
  } else {
    Serial.println("Stepper: Initialization Failed");
  }
}

void StepperController::setSpeed(uint32_t speed) {
  if (s_stepper) {
    s_stepper->setSpeedInHz(speed);
    if (s_stepper->isRunning()) {
      s_stepper->applySpeedAcceleration();
    }
  }
}

void StepperController::runForward() {
  if (s_stepper) s_stepper->runForward();
}

void StepperController::runBackward() {
  if (s_stepper) s_stepper->runBackward();
}

void StepperController::stop() {
  if (s_stepper) s_stepper->stopMove();
}

bool StepperController::isRunning() { return s_stepper && s_stepper->isRunning(); }
