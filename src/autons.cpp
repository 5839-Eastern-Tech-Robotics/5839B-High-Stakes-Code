#include "autons.hpp"
#include "globals.hpp"
#include "pros/rtos.hpp"
#include "robot/subsytems/intake.hpp"

void red_auton() {
  chassis.chassis()->setPose({-57, -32, 270});
  clamp.retract();
  chassis.chassis()->moveToPose(-29, -22, 240, 2000, { .forwards = false, .minSpeed = 100, .earlyExitRange = 5 });
  chassis.chassis()->waitUntil(25);
  clamp.extend();
  pros::delay(1000);
  intakeHookMotor.move(127);
  intakeMotor.move(127);
  pros::delay(750);
  chassis.chassis()->turnToPoint(-6, -22, 2000);
  chassis.chassis()->moveToPoint(-6, -22, 2000, { .maxSpeed = 40 });
  pros::delay(10000);
  intakeHookMotor.move(0);
  intakeMotor.move(0);
  intake.setColorFilter(Color::Blue);
}

void red_auton_v2() {}

void blue_auton() {
  chassis.chassis()->setPose({57, -32, 90});
  clamp.retract();
  chassis.chassis()->moveToPoint(22, -22, 2000, { .forwards = false, .maxSpeed = 75 });
  chassis.chassis()->waitUntil(30);
  clamp.extend();
  pros::delay(1000);
  intakeHookMotor.move(127);
  intakeMotor.move(127);
  pros::delay(750);
  chassis.chassis()->turnToPoint(6, -22, 2000);
  chassis.chassis()->moveToPoint(6, -22, 2000, { .maxSpeed = 40 });
  pros::delay(10000);
  intakeHookMotor.move(0);
  intakeMotor.move(0);
  intake.setColorFilter(Color::Blue);
}

void blue_auton_v2() {
  chassis.chassis()->setPose({57, -32, 90});
  clamp.retract();
  chassis.chassis()->moveToPoint(22, -22, 2000, { .forwards = false, .maxSpeed = 75 });
  chassis.chassis()->waitUntil(30);
  clamp.extend();
  pros::delay(1000);
  intakeHookMotor.move(127);
  intakeMotor.move(127);
  pros::delay(1500);
  chassis.chassis()->turnToPoint(24, -48, 1000);
  chassis.chassis()->moveToPoint(24, -48, 2000);
  pros::delay(10000);
  intakeHookMotor.move(0);
  intakeMotor.move(0);
  intake.setColorFilter(Color::Blue);
}

void skills() {
  pros::Task subsystems([&]() {
      while (true) {
        intake.update();
        pros::delay(25);
      }
  });

  chassis.chassis()->setPose({-60, 0, 90});
  clamp.retract();
  intake.intakeToMogo();
  pros::delay(1000);
  intake.stop();
  chassis.chassis()->moveToPoint(-56, 0, 1000);

  chassis.chassis()->turnToPoint(-45, -27, 1000, { .forwards = false });
  chassis.chassis()->moveToPose(-44,3-27, 0, 2000, { .forwards = false, .minSpeed = 100, .earlyExitRange = 5 });
  chassis.chassis()->waitUntil(24);
  chassis.chassis()->cancelMotion();
  pros::delay(200);
  clamp.extend();
  pros::delay(250);

  intake.intakeToMogo();
  chassis.chassis()->turnToPoint(-30, -24, 1000);
  chassis.chassis()->moveToPoint(-30, -24, 2000, { .minSpeed = 100, .earlyExitRange = 5 });
  chassis.chassis()->waitUntilDone();
  pros::delay(1000);

  chassis.chassis()->turnToPoint(-20, -48, 1000);
  chassis.chassis()->moveToPoint(-20, -48, 2000, { .minSpeed = 100 });
  chassis.chassis()->waitUntilDone();
  pros::delay(1000);

  chassis.chassis()->turnToPoint(-48, -60, 1000);
  chassis.chassis()->moveToPoint(-48, -60, 1000);
  pros::delay(1000);

  chassis.chassis()->turnToPoint(-70, -70, 1000, { .forwards = false });
  chassis.chassis()->moveToPoint(-70, -70, 1000, { .forwards = false });
  pros::delay(500);
  clamp.retract();

  chassis.chassis()->moveToPoint(-60, -60, 1000);
}

void red_no_sawp() {
    chassis.chassis()->setPose({-58, 42, 120});
    chassis.chassis()->moveToPose(-31, 28, 120, 2000);
    chassis.chassis()->waitUntilDone();
    pros::delay(500);
    pros::delay(500);
    clamp.extend();
    chassis.chassis()->moveToPose(-47, 6, 0, 2000, { .forwards = false });
    chassis.chassis()->waitUntil(15);
    intakeMotor.move(127);
    chassis.chassis()->waitUntilDone();
    pros::delay(500);
    chassis.chassis()->moveToPose(-60, 35, 270, 2000);
    pros::delay(1000);
    intakeMotor.move(0);
    chassis.chassis()->moveToPose(-32, 47, 270, 2000, { .forwards = false });
    chassis.chassis()->waitUntil(20);
    intakeMotor.move(127);
    chassis.chassis()->waitUntilDone();
    pros::delay(500);
    chassis.chassis()->moveToPose(-10, 43, 270, 2000, { .forwards = false });
    pros::delay(1000);
    intakeMotor.move(0);
    chassis.chassis()->waitUntil(10);
    intakeMotor.move(127);
    chassis.chassis()->waitUntilDone();
    pros::delay(500);
    chassis.chassis()->turnToPoint(-3.5, 50, 1000, { .forwards = false });
    chassis.chassis()->moveToPoint(-3.5, 50, 1000, { .forwards = false });
}