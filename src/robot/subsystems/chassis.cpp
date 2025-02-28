#include "robot/subsytems/chassis.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include <cstdint>
#include <cstdlib>

#define DRIVING_ENCODER_POS 2260
#define E_STOP_MIN 1000
#define E_STOP_MAX 3800

bool is_close(int a, int b, int epsilon = 100) {
  return std::abs(a - b) <= epsilon;
}

Chassis::Chassis(lemlib::Chassis *m6, lemlib::Chassis *m4,
                 pros::adi::Pneumatics pto, pros::MotorGroup *ladybrown,
                 pros::adi::Potentiometer ladybrownPos,
                 lemlib::PID ladybrownPid)
    : m4(m4), m6(m6), pto(pto), ladybrown(ladybrown),
      ladybrownPos(ladybrownPos), ladybrownPid(ladybrownPid) {}

void Chassis::move(int8_t vel) { this->desiredManualVel = vel; }

void Chassis::toggleLock() { this->locked = !this->locked; }
void Chassis::lock(ChassisState state) {
  this->currentState = state;
  this->locked = true;
}

lemlib::Chassis *Chassis::chassis() {
  if (this->currentState == ChassisState::Driving)
    return this->m6;
  return this->m4;
}

void Chassis::update() {
  switch (this->currentState) {
  case Driving:
    updateDriving();
    break;
  case Cooldown:
    updateCooldown();
    break;
  case Manual:
    updateManual();
    break;
  }
}

void Chassis::updateDriving() {
  if (this->desiredManualVel != 0 && !this->locked)
    this->currentState = ChassisState::Manual;

  if (this->pto.is_extended())
    this->pto.retract();
}

void Chassis::updateManual() {
  if (!this->pto.is_extended()) this->pto.extend();

  if (this->ladybrownPos.get_value() <= E_STOP_MIN && this->desiredManualVel > 0)
    this->ladybrown->move(0);
  else if (this->ladybrownPos.get_value() >= E_STOP_MAX && this->desiredManualVel < 0)
    this->ladybrown->move(0);
  else
    this->ladybrown->move(this->desiredManualVel);

  if (this->desiredManualVel == 0 && this->ladybrownPos.get_value() > DRIVING_ENCODER_POS && !this->locked) {
    this->currentState = ChassisState::Cooldown;
    this->cooldownTime = pros::millis() + 1000;
  }
}

void Chassis::updateCooldown() {
  if (this->desiredManualVel != 0 || this->ladybrownPos.get_value() < DRIVING_ENCODER_POS)
    this->currentState = ChassisState::Manual;

  if (pros::millis() > this->cooldownTime)
    this->currentState = ChassisState::Driving;
}