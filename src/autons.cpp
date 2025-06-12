#include "autons.hpp"
#include "globals.hpp"
#include "pros/rtos.hpp"
#include "robot/subsytems/chassis.hpp"
#include "robot/subsytems/intake.hpp"

void red_auton() {
	chassis.setPose({-57, -32, 270});
	clamp.extend();
	chassis.moveToPose(-29, -22, 240, 2000, { .forwards = false, .minSpeed = 100, .earlyExitRange = 5 });
	chassis.waitUntil(25);
	clamp.retract();
	pros::delay(1000);
	intakeHookMotor.move(127);
	intakeMotor.move(127);
	pros::delay(750);
	chassis.turnToPoint(-6, -22, 2000);
	chassis.moveToPoint(-6, -22, 2000, { .maxSpeed = 40 });
	pros::delay(10000);
	intakeHookMotor.move(0);
	intakeMotor.move(0);
	intake.setColorFilter(Color::Blue);
}

void red_auton_v2() {
	chassis.setPose({-57, -32, 270});
	clamp.extend();
	chassis.moveToPose(-29, -22, 240, 2000, { .forwards = false, .minSpeed = 100, .earlyExitRange = 5 });
	chassis.waitUntil(25);
	clamp.retract();
	pros::delay(1000);
	intakeHookMotor.move(127);
	intakeMotor.move(127);
	pros::delay(750);
	chassis.turnToPoint(-6, -22, 2000);
	chassis.moveToPoint(-6, -22, 2000, { .maxSpeed = 40 });
	pros::delay(10000);
	intakeHookMotor.move(0);
	intakeMotor.move(0);
	intake.setColorFilter(Color::Blue);

}

void blue_auton() {
	chassis.setPose({57, -32, 90});
	clamp.extend();
	chassis.moveToPoint(22, -22, 2000, { .forwards = false, .maxSpeed = 75 });
	chassis.waitUntil(30);
	clamp.retract();
	pros::delay(1000);
	intakeHookMotor.move(127);
	intakeMotor.move(127);
	pros::delay(750);
	chassis.turnToPoint(6, -22, 2000);
	chassis.moveToPoint(6, -22, 2000, { .maxSpeed = 40 });
	pros::delay(10000);
	intakeHookMotor.move(0);
	intakeMotor.move(0);
	intake.setColorFilter(Color::Blue);
}

void blue_auton_v2() {
	chassis.setPose({57, -32, 90});
	clamp.extend();
	chassis.moveToPoint(22, -22, 2000, { .forwards = false, .maxSpeed = 75 });
	chassis.waitUntil(30);
	clamp.retract();
	pros::delay(1000);
	intakeHookMotor.move(127);
	intakeMotor.move(127);
	pros::delay(750);
	chassis.turnToPoint(24, -48, 100);
	deringer.toggle();
	pros::delay(300);
	deringer.toggle();
	chassis.moveToPoint(24, -42, 2000);
	chassis.waitUntilDone();
	pros::delay(1000);
	intakeHookMotor.move(0);
	intakeMotor.move(0);
	chassis.turnToPoint(8, -8, 2000);
	chassis.moveToPoint(8, -8, 2000, { .maxSpeed = 60 });
	pros::delay(10000);
	intake.setColorFilter(Color::Blue);
}

ASSET(path_7_txt);

void skills() {
	pros::Task subsystems([&]() {
			while (true) {
				intake.update();
				chassis.update();
				pros::delay(25);
			}
	});

	chassis.setPose({-60, 0, 90});
	clamp.extend();
	intake.intakeToMogo();
	pros::delay(1000);
	intake.stop();
	chassis.moveToPoint(-56, 0, 1000);

	chassis.turnToPoint(-45, -27, 1000, { .forwards = false });
	chassis.moveToPose(-44,3-27, 0, 2000, { .forwards = false, .minSpeed = 100, .earlyExitRange = 5 });
	chassis.waitUntil(24);
	chassis.cancelMotion();
	pros::delay(200);
	clamp.retract();
	pros::delay(250);

	intake.intakeToMogo();
	chassis.turnToPoint(-30, -24, 1000);
	chassis.moveToPoint(-30, -24, 2000, { .minSpeed = 100, .earlyExitRange = 5 });
	chassis.waitUntilDone();
	pros::delay(1000);

	chassis.turnToPoint(-20, -48, 1000); // -20, -48 is the start of 4
	chassis.moveToPoint(-20, -48, 2000, { .minSpeed = 100, .earlyExitRange = 5 }); // this is 3 i think
	chassis.waitUntilDone();
	pros::delay(1000);

	chassis.turnToPoint(-45, -60, 1000);
	chassis.moveToPoint(-45, -60, 1000, { .minSpeed = 100, .earlyExitRange = 5 }); // since the last motion went over in the negative y direction, this motion is angled slightly in the positive y direction, but it seems to be in the nonpositive y direction and predominantly in the negative x direction
	chassis.waitUntilDone();
	pros::delay(1000);

	chassis.turnToPoint(-70, -70, 1000, { .forwards = false }); // turn around
	chassis.moveToPoint(-70, -70, 1000, { .forwards = false }); // go to corner
	pros::delay(500);
	clamp.extend();

	chassis.moveToPoint(-60, -60, 1000);
	chassis.moveToPoint(-50, -50, 1000);

	chassis.turnToPoint(-48, 24, 1000, { .forwards = false });
	chassis.moveToPoint(-48, 24, 4000, { .forwards = false });
	chassis.waitUntil(95);
	clamp.retract();
	pros::delay(1000);

	chassis.moveToPoint(-70, 70, 3000, { .forwards = false });

	// chassis.follow(path_7_txt, 15, 5000);
}

void red_no_sawp() {
		chassis.setPose({-58, 42, 120});
		chassis.moveToPose(-31, 28, 120, 2000);
		chassis.waitUntilDone();
		pros::delay(500);
		pros::delay(500);
		clamp.retract();
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
