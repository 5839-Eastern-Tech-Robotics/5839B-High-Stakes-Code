#include "robot/subsytems/intake.hpp"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rtos.hpp"
#include <cstdio>

Intake::Intake(pros::Motor intakeMotor, pros::Motor hookMotor,
               pros::Optical colorSensor, pros::ADIDigitalIn limitSwitch)
    : intakeMotor(intakeMotor), hookMotor(hookMotor), colorSensor(colorSensor),
      currentState(State::Idle), currentRing(Color::None),
      ringDestination(Destination::Mogo), limitSwitch(limitSwitch) {}

void Intake::update() {
  switch (currentState) {
    case State::Idle:
      updateIdle();
      break;
    case State::Outtaking:
      updateOuttaking();
      break;
    case State::Ejecting:
      updateEjecting();
      break;
    case State::EjectStop:
      updateEjectStop();
      break;
    case State::Intaking:
      updateIntaking();
      break;
    case State::IntakeLift:
      updateIntakeLift();
      break;
    case State::LiftReverse:
      updateLiftReverse();
      break;
    case State::IntakeMogo:
      updateIntakeMogo();
      break;
  }
}

void Intake::stop() { currentState = State::Idle; }

void Intake::outtake() {
    currentState = State::Outtaking;
}

void Intake::intakeToLift() {
  currentState = State::Intaking;
  ringDestination = Destination::Lift;
}

void Intake::intakeToMogo() {
  currentState = State::Intaking;
  ringDestination = Destination::Mogo;
}

void Intake::setColorFilter(Color filter) {
  this->filter = filter;
}

Color Intake::getCurrentRingColor() { return currentRing; }

void Intake::updateIdle() {
  this->intakeMotor.move(0);
  this->hookMotor.move(0);

  if (this->colorSensor.get_proximity() < 200) {
    printf("No Ring Detected\n");
    return;
  }

  printf("%s Ring Detected\n",
         this->colorSensor.get_hue() > 300 || this->colorSensor.get_hue() < 50
             ? "Red"
         : this->colorSensor.get_hue() > 150 &&
                 this->colorSensor.get_hue() < 250
             ? "Blue"
             : "Other");
}

void Intake::updateIntaking() {
  this->intakeMotor.move(127);
  this->hookMotor.move(127);

  if (this->colorSensor.get_proximity() < 200)
    return;

  this->ringStart = this->hookMotor.get_position();

  this->currentRing =
      this->colorSensor.get_hue() > 300 || this->colorSensor.get_hue() < 50
          ? Color::Red
      : this->colorSensor.get_hue() > 150 && this->colorSensor.get_hue() < 250
          ? Color::Blue
          : Color::None;

  if (this->filter == Color::None) {
    if (this->ringDestination == Destination::Lift)
      this->currentState = State::IntakeLift;
    else
      this->currentState = State::IntakeMogo;
    return;
  }

  if (this->filter == Color::All) {
    this->currentState = State::Ejecting;
    return;
  }

  if (this->filter == this->currentRing) {
    this-> currentState = State::Ejecting;
    return;
  }

  if (this->ringDestination == Destination::Lift)
    this->currentState = State::IntakeLift;
  else
    this->currentState = State::IntakeMogo;
}

void Intake::updateOuttaking() {
  this->intakeMotor.move(-127);
  this->hookMotor.move(-127);
}

void Intake::updateEjecting() {
  this->intakeMotor.move(127);
  this->hookMotor.move(127);

  // if (this->hookMotor.get_position() - this->ringStart >= this->EJECT_OFFSET)
  if (this->limitSwitch.get_new_press()) {
    this->ejectTimer = -1;
    this->currentState = State::EjectStop;
  }
}

void Intake::updateEjectStop() {
  this->hookMotor.move(-127);
  printf("eject timer: %i; time left: %i\n", ejectTimer,
         ejectTimer - pros::millis());
  if (this->ejectTimer < 0) {
    this->ejectTimer = pros::millis() + 250;
  }

  if ((ejectTimer - pros::millis()) <= 0) {
    this->ejectTimer = -1;
    this->currentState = State::Intaking;
  }
}

void Intake::updateIntakeLift() {
  this->intakeMotor.move(127);
  this->hookMotor.move(127);
  // if (this->hookMotor.get_position() - this->ringStart >=
  // this->LIFT_REVERSE_OFFSET) {
  if (this->limitSwitch.get_new_press()) {
    this->currentState = State::LiftReverse;
    this->ringStart = hookMotor.get_position();
  }
}

void Intake::updateLiftReverse() {
  this->hookMotor.move(-127);
  if (this->hookMotor.get_position() - this->ringStart <= this->LIFT_OFFSET)
    this->currentState = State::Intaking;
}

void Intake::updateIntakeMogo() {
  this->intakeMotor.move(127);
  this->hookMotor.move(127);
  if (this->hookMotor.get_position() - this->ringStart >= this->MOGO_OFFSET)
    this->currentState = State::Intaking;
}
