#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pid.hpp"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include <cstdint>

enum ChassisState {
  Intake,
  Driving,
  Ready,
  Score,
  ManualControl,
};

class Chassis {
public:
  Chassis(lemlib::Chassis *m6, lemlib::Chassis *m4, pros::adi::Pneumatics pto,
          pros::MotorGroup *ladybrown, pros::adi::Potentiometer ladybrownPos,
          lemlib::PID ladybrownPid);
  void update();
  ChassisState nextState();
  ChassisState prevState();
  void toState(ChassisState pos);
  void move(int8_t vel);
  lemlib::Chassis *chassis();

private:
  void updateIntake();
  void updateDriving();
  void updateReady();
  void updateScore();
  void updateManual();

  lemlib::Chassis *m6;
  lemlib::Chassis *m4;
  pros::adi::Pneumatics pto;
  pros::MotorGroup *ladybrown;
  lemlib::PID ladybrownPid;
  pros::adi::Potentiometer ladybrownPos;
  ChassisState currentState = ChassisState::Driving;
  int8_t desiredManualVel = 0;
};
