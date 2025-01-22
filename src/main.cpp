#include "main.h"
#include "autons.hpp"
#include "globals.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "robodash/views/selector.hpp"
#include "robot/subsytems/intake.hpp"
#include "robodash/api.h"
#include "autons.hpp"


rd::Selector selector({
  {"Red Alliance", red_auton, "", 5},
  {"Blue Alliance", blue_auton, "", 240},
  {"Skills", skills}
});

void initialize() {
  // pros::lcd::initialize();
  controller.clear();
  chassis.calibrate();
  intake.setIntakeSpeed(127);

  pros::Task screenTask([&]() {
    while (false) {
      pros::lcd::print(0, "X: %f", chassis.getPose().x);
      pros::lcd::print(1, "Y: %f", chassis.getPose().y);
      pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);

      controller.print(
          0, 0, "Filter Out: %s",
          intake.filter == Color::None
              ? "None"
              : (intake.filter == Color::Blue
                     ? "Blue"
                     : (intake.filter == Color::Red ? "Red" : "All")));

      pros::lcd::print(
          3, "State: %s",
          intake.currentState == State::Idle
              ? "Idle"
              : (intake.currentState == State::Intaking
                     ? "Intaking"
                     : (intake.currentState == State::Ejecting
                            ? "Ejecting"
                            : (intake.currentState == State::EjectStop
                                   ? "Eject Stop"
                                   : (intake.currentState == State::IntakeHold
                                          ? "Intake Hold"
                                          : (intake.currentState ==
                                                     State::IntakeMogo
                                                 ? "Intake Mogo"
                                                 : (intake.currentState ==
                                                            State::Outtaking
                                                        ? "Outtaking"
                                                        : "Other")))))));

      // pros::lcd::print(3, "BR: %f, MR: %f, FR: %f",
      //     rightMotors.get_actual_velocity_all()[0],
      //     rightMotors.get_actual_velocity_all()[1],
      //     rightMotors.get_actual_velocity_all()[2]
      // );
      // pros::lcd::print(3, "BL: %f, ML: %f, FL: %f",
      //     leftMotors.get_actual_velocity_all()[0],
      //     leftMotors.get_actual_velocity_all()[1],
      //     leftMotors.get_actual_velocity_all()[2]
      // );
      pros::lcd::print(
          4, "Ring: %s",
          intake.getCurrentRingColor() == Color::Blue
              ? "Blue"
              : (intake.getCurrentRingColor() == Color::Red ? "Red" : "None"));
      pros::lcd::print(5, "Color Sensor: %f", (float)colorSensor.get_hue());
      pros::lcd::print(6, "Switch: %s", ringSwitch.get_value() ? "true" : "false");
      // pros::lcd::print(2, "Distance Sensor: %f",
      //                  (float)colorSensor.get_proximity());
      // pros::lcd::print(4, "Hook Motor: %f",
      //                  (float)intakeHookMotor.get_position());
      pros::delay(50);
    }
  });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  skills();
  return;
  selector.run_auton();
  // red_no_sawp();
}

void opcontrol() {
  // release the intake thingy
  // intakeHookMotor.move(127);
  // pros::delay(250);
  // intakeMotor.move(0);

  // skills();
  // return;

  // red_no_sawp();
  // return;

  // chassis.setPose({0, 0, 0});
  // chassis.turnToHeading(90, 10000);
  // chassis.moveToPoint(0, 24, 10000);
  // chassis.moveToPose(24, 48, 90, 10000);

  // Left Triggers: Toggle Intake
  // Right Triggers: Hold for Intake
  // X: clamp
  // Y: color filter switch
  // Up: wheel toggle

  bool intakeToggle = false;

  while (true) {
    intake.update();
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    if (PTO.is_extended())
      chassisPTO.curvature(leftY, rightX);
    else
      chassis.curvature(leftY, rightX);

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      intakeToggle = true;
      if (intake.currentState == State::IntakeMogo || intake.currentState == State::Intaking) {
        intake.stop();
      } else {
        intake.intakeToMogo();
      }
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      intakeToggle = true;
      if (intake.currentState == State::Outtaking) {
        intake.stop();
      } else {
        intake.outtake();
      }
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      intakeToggle = true;
      if (intake.currentState == State::IntakeHold)
        intake.stop();
      else
        intake.intakeToHold();
    }

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      intakeToggle = false;
      intake.intakeToMogo();
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      intakeToggle = false;
      intake.outtake();
    } else if (!intakeToggle) {
      intake.stop();
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      if (intake.filter == Color::Blue)
        intake.setColorFilter(Color::Red);
      else
        intake.setColorFilter(Color::Blue);
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
      intake.setColorFilter(Color::None);

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
      clamp.toggle();

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
      PTO.toggle();

    pros::delay(25);
  }
}
