#include "StepperController.h"
#include <Arduino.h>

static FastAccelStepperEngine engine = FastAccelStepperEngine();

FastAccelStepper* StepperController::s_stepper = nullptr;

StepperController::StepperController(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin)
	: _stepPin(stepPin), _dirPin(dirPin), _enablePin(enablePin) {}

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

FastAccelStepper* StepperController::getStepper() {
	return s_stepper;
}

