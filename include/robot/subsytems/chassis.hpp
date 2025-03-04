#pragma once

#include "globals.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pid.hpp"
#include "lemlib/pose.hpp"
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

  void setPose(lemlib::Pose);
  lemlib::Pose getPose(bool radians, bool standardPos);

  void turnToPoint(float x, float y, int timeout, lemlib::TurnToPointParams params = {}, bool async = true);
  void turnToHeading(float theta, int timeout, lemlib::TurnToHeadingParams params = {}, bool async = true);
  void moveToPoint(float x, float y, int timeout, lemlib::MoveToPointParams params = {}, bool async = true);
  void moveToPose(float x, float y, float theta, int timeout, lemlib::MoveToPoseParams params = {}, bool async = true);
  void follow(const asset &path, float lookahead, int timeout, bool forwards = true, bool async = true);

  void waitUntil(float dist);
  void waitUntilDone();
  void cancelMotion();

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
