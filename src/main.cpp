#include "main.h"
#include "autons.hpp"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "robodash/views/selector.hpp"
#include "robot/subsytems/chassis.hpp"
#include "robot/subsytems/intake.hpp"
#include "robot/ui/lcd.hpp"

rd::Selector selector({
  {"Red Alliance", red_auton, "", 5},
  {"Blue Alliance", blue_auton, "", 240},

  {"Red Alliance V2", red_auton_v2, "", 5},
  {"Blue Alliance V2", blue_auton_v2, "", 240},

  {"Skills", skills}
});

LCD lcd{};

void initialize() {
  controller.clear();
  m4.calibrate();
  m6.calibrate();
  intake.setIntakeSpeed(127);

  pros::Task screenTask([&]() {
    while (true) {
      // lcd.printf(0, "X: %f", chassis.chassis()->getPose().x);
      // lcd.printf(1, "Y: %f", chassis.chassis()->getPose().y);
      // lcd.printf(2, "Theta: %f", chassis.chassis()->getPose().theta);

      // lcd.printf(3, "Encoder Value:  %d", ladybrownPot.get_value());
      // lcd.printf(4, "Desired Velocity %d", chassis.desiredManualVel);
      // lcd.printf(5, "State: %s",
      //                  chassis.currentState == ChassisState::Manual
      //                      ? "Manual"
      //                      : (chassis.currentState == ChassisState::Cooldown
      //                             ? "Cooldown"
      //                             : "Driving"));

      controller.print(
          0, 0, "Filter: %s",
          intake.filter == Color::None
              ? "None"
              : (intake.filter == Color::Blue
                     ? "Blue"
                     : (intake.filter == Color::Red ? "Red" : "All")));

      pros::delay(50);
    }
  });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  selector.run_auton();
}

void opcontrol() {
  bool intakeToggle = false;
  bool debugMode = false;

  while (true) {
    intake.update();
    chassis.update();

    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    chassis.chassis()->curvature(leftY, rightX);

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      intakeToggle = true;
      if (intake.currentState == State::IntakeHold)
        intake.stop();
      else
        intake.intakeToHold();
    }

    if (!debugMode && controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      intakeToggle = false;
      intake.intakeToMogo();
    } else if (!debugMode && controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      intakeToggle = false;
      intake.outtake();
    } else if (!intakeToggle) {
      intake.stop();
    }

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      chassis.move(127);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      chassis.move(-127);
    } else {
      chassis.move(0);
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

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
      deringer.toggle();

    if ((controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) ||
        (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)))
      debugMode = !debugMode;

    if (debugMode && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      intakeToggle = true;
      if (intake.currentState == State::IntakeMogo ||
          intake.currentState == State::Intaking) {
        intake.stop();
      } else {
        intake.intakeToMogo();
      }
      }
    }
    }

    if (debugMode && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      intakeToggle = true;
      if (intake.currentState == State::Outtaking) {
        intake.stop();
      } else {
        intake.outtake();
      }
    }

    if (debugMode && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
      chassis.toggleLock();

    pros::delay(25);
  }
}
