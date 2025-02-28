#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pid.hpp"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include <cstdint>

enum ChassisState {
  Driving,
  Manual,
  Cooldown,

};

class Chassis {
public:
  Chassis(lemlib::Chassis *m6, lemlib::Chassis *m4, pros::adi::Pneumatics pto,
          pros::MotorGroup *ladybrown, pros::adi::Potentiometer ladybrownPos,
          lemlib::PID ladybrownPid);
  void update();
  void toggleLock();
  void lock(ChassisState state);
  void move(int8_t vel);
  lemlib::Chassis *chassis();

  ChassisState currentState = ChassisState::Driving;
  int8_t desiredManualVel = 0;

private:
  void updateDriving();
  void updateManual();
  void updateCooldown();

  lemlib::Chassis *m6;
  lemlib::Chassis *m4;
  pros::adi::Pneumatics pto;
  pros::MotorGroup *ladybrown;
  lemlib::PID ladybrownPid;
  pros::adi::Potentiometer ladybrownPos;
  uint cooldownTime = -1;
  bool locked = false;
};
