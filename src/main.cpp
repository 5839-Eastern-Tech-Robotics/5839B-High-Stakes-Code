#include "main.h"
#include "globals.hpp"
#include "pros/llemu.hpp"
// #include "autons.hpp"

void initialize() {
    pros::lcd::initialize();

    pros::Task screenTask([&]() {
        while (true) {
            pros::lcd::print(0, "X: %f", chassis.getPose().x);
            pros::lcd::print(1, "Y: %f", chassis.getPose().y);
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
            pros::lcd::print(3, "BR: %f, MR: %f, FR: %f", 
                rightMotors.get_actual_velocity_all()[0], 
                rightMotors.get_actual_velocity_all()[1], 
                rightMotors.get_actual_velocity_all()[2]
            );
            pros::lcd::print(3, "BL: %f, ML: %f, FL: %f", 
                leftMotors.get_actual_velocity_all()[0], 
                leftMotors.get_actual_velocity_all()[1], 
                leftMotors.get_actual_velocity_all()[2]
            );
            pros::delay(50);
        }
    });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    // red_no_sawp();
}

void opcontrol() {
    int intakeMotorOn = 0;
    while (true) {
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        if (PTO.is_extended()) chassisPTO.curvature(leftY, rightX);
        else chassis.curvature(leftY, rightX);

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
          if (intakeMotorOn == 0 || intakeMotorOn == -1)
            intakeMotorOn = 1;
          else
            intakeMotorOn = 0;
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
          if (intakeMotorOn == 0 || intakeMotorOn == 1)
            intakeMotorOn = -1;
          else
            intakeMotorOn = 0;
        }

        if (intakeMotorOn == 1) {
            intakeMotor.move(127);
            intakeHookMotor.move(127);
        } else if (intakeMotorOn == -1) {
            intakeMotor.move(-127);
            intakeHookMotor.move(-127);
        } else {
            intakeMotor.move(0);
            intakeHookMotor.move(0);
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
            clamp.toggle();

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
            PTO.toggle();

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intakeLiftMotor.move(127);
            /*intakeLiftSetPoint = 50;*/
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intakeLiftMotor.move(-127);
            /*intakeLiftSetPoint = 0;*/
        } else {
            intakeLiftMotor.move(0);
        }

        /*if (intakeLiftSetPoint - intakeLiftSensor.get_angle() > 5) {*/
        /*    PTO.retract();*/
        /*    intakeLiftMotor.move(127);*/
        /*} else if (intakeLiftSetPoint - intakeLiftSensor.get_angle() < -5) {*/
        /*    PTO.retract();*/
        /*    intakeLiftMotor.move(-127);*/
        /*} else {*/
        /*    intakeLiftMotor.move(0);*/
        /*    PTO.extend();*/
        /*}*/

        pros::delay(10);
    }
}
