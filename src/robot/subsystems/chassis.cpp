#include "robot/subsytems/chassis.hpp"
#include "lemlib/chassis/chassis.hpp"
#include <cstdint>

#define INTAKE_ENCODER_POS 3720
#define DRIVING_ENCODER_POS 3480
#define READY_ENCODER_POS 2160
#define SCORE_ENCODER_POS 1430

Chassis::Chassis(lemlib::Chassis *m6, lemlib::Chassis *m4,
                 pros::adi::Pneumatics pto, pros::MotorGroup *ladybrown,
                 pros::adi::Potentiometer ladybrownPos,
                 lemlib::PID ladybrownPid)
    : m4(m4), m6(m6), pto(pto), ladybrown(ladybrown),
      ladybrownPos(ladybrownPos), ladybrownPid(ladybrownPid) {}

ChassisState Chassis::nextState() {
  if (this->currentState == ChassisState::ManualControl)
    return this->currentState = ChassisState::Driving;
  return this->currentState = (ChassisState)(((int)this->currentState + 1) % 4);
}

ChassisState Chassis::prevState() {
  if (this->currentState == ChassisState::ManualControl)
    return this->currentState = ChassisState::Driving;
  return this->currentState = (ChassisState)(((int)this->currentState + 3) % 4);
}

void Chassis::toState(ChassisState pos) { this->currentState = pos; }

void Chassis::move(int8_t vel) { this->desiredManualVel = vel; }

lemlib::Chassis *Chassis::chassis() {
  if (this->currentState == ChassisState::Driving)
    return this->m6;
  return this->m4;
}

void Chassis::update() {
  switch (this->currentState) {
  case Intake:
    updateIntake();
    break;
  case Driving:
    updateDriving();
    break;
  case Ready:
    updateReady();
    break;
  case Score:
    updateScore();
    break;
  case ManualControl:
    updateManual();
    break;
  }
}

void Chassis::updateIntake() {
  if (!this->pto.is_extended()) this->pto.extend();
  this->ladybrown->move(this->ladybrownPid.update(INTAKE_ENCODER_POS - this->ladybrownPos.get_value()));
}

void Chassis::updateDriving() {
  this->ladybrown->move(0);
  if (this->pto.is_extended()) this->pto.retract();
}

void Chassis::updateReady() {
  if (!this->pto.is_extended()) this->pto.extend();
  this->ladybrown->move(this->ladybrownPid.update(READY_ENCODER_POS - this->ladybrownPos.get_value()));
}

void Chassis::updateScore() {
  if (!this->pto.is_extended()) this->pto.extend();
  this->ladybrown->move(this->ladybrownPid.update(SCORE_ENCODER_POS - this->ladybrownPos.get_value()));
}

void Chassis::updateManual() {
  if (!this->pto.is_extended()) this->pto.extend();
  this->ladybrown->move(this->desiredManualVel);
}