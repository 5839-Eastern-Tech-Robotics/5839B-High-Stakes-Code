#include "autons.hpp"
#include "globals.hpp"

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