#include "autons.hpp"
#include "globals.hpp"
#include "pros/rtos.hpp"

void red_auton() {
  chassis.moveToPoint(
      0, 37, 2000, {.forwards = false, .minSpeed = 50, .earlyExitRange = 10});
  chassis.moveToPoint(0, 37, 2000, {.forwards = false, .maxSpeed = 50});
  clamp.extend();
  intakeHookMotor.move(127);
  pros::delay(750);
  intakeMotor.move(0);
  intake.setColorFilter(Color::Blue);
}

void blue_auton() {
  chassis.moveToPoint(
      0, 37, 2000, {.forwards = false, .minSpeed = 50, .earlyExitRange = 10});
  chassis.moveToPoint(0, 37, 2000, {.forwards = false, .maxSpeed = 50});
  clamp.extend();
  intakeHookMotor.move(127);
  pros::delay(750);
  intakeMotor.move(0);
  intake.setColorFilter(Color::Red);
}

void skills() {
  chassis.setPose({-60, 0, 90});
  clamp.retract();
  intakeHookMotor.move(127);
  pros::delay(1000);
  intakeHookMotor.move(0);
  chassis.moveToPoint(-56, 0, 1000);
  chassis.turnToPoint(-45, -27, 1000, {.forwards = false});
  chassis.moveToPose(-45, -24, 0, 2000, { .forwards = false, .maxSpeed = 120 });
                    //  {.forwards = false, .minSpeed = 100, .earlyExitRange = 5});
  chassis.waitUntil(24);
  // pros::delay(250);
  clamp.extend();
  pros::delay(250);
  chassis.turnToPoint(-24, -24, 1000);
  return;
  chassis.moveToPoint(
      -60, -60, 2000,
      {.forwards = false, .minSpeed = 100, .earlyExitRange = 5});
  // clamp.retract();
  chassis.moveToPoint(-72, -72, 2000, {.forwards = false});
  // chassis.moveToPoint(-50, -50, 2000);
  // chassis.moveToPoint()
  // chassis.setPose({-58, -17, 120});
  // chassis.moveToPoint(-52, -21, 2000, {.maxSpeed = 50, .forwards = false});
  // clamp.extend();
  // chassis.turnToHeading(270, 1000);
  // intake.intakeToMogo();
  // chassis.moveToPoint(-23.5, -23.5, 2000, { .earlyExitRange = 3, .minSpeed =
  // 50 }); chassis.moveToPoint(-23.5, -23.5, 2000, { .maxSpeed = 50 });
  // chassis.turnToHeading(180, 1000);
  // chassis.moveToPoint(-24, -48, 2000, { .earlyExitRange = 3, .minSpeed = 50
  // }); chassis.moveToPoint(-24, -48, 2000, { .maxSpeed = 50 });
}

void red_no_sawp() {
    chassis.setPose({-58, 42, 120});
    chassis.moveToPose(-31, 28, 120, 2000);
    chassis.waitUntilDone();
    pros::delay(500);
    pros::delay(500);
    clamp.extend();
    chassis.moveToPose(-47, 6, 0, 2000, { .forwards = false });
    chassis.waitUntil(15);
    intakeMotor.move(127);
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPose(-60, 35, 270, 2000);
    pros::delay(1000);
    intakeMotor.move(0);
    chassis.moveToPose(-32, 47, 270, 2000, { .forwards = false });
    chassis.waitUntil(20);
    intakeMotor.move(127);
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPose(-10, 43, 270, 2000, { .forwards = false });
    pros::delay(1000);
    intakeMotor.move(0);
    chassis.waitUntil(10);
    intakeMotor.move(127);
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.turnToPoint(-3.5, 50, 1000, { .forwards = false });
    chassis.moveToPoint(-3.5, 50, 1000, { .forwards = false });
}