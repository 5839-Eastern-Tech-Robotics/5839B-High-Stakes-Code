#pragma once

#include "pros/motors.hpp"
#include "pros/optical.hpp"

class Intake {

enum Color {
  Red,
  Blue,
  All,
  None
};

enum Destination {
  Mogo,
  Lift
};

public:
  Intake(pros::Motor intakeMotor, pros::Motor hookMotor, pros::Optical colorSensor);
  void update();
  void intakeToMogo();
  void intakeToLift();
  void outtake();
  /**
   * sets the color filter
   * @param filter the color to eject
   */
  void setColorFilter(Color filter);
  /**
   * gets the color of the ring thats currently in the intake
   * @returns the color of the ring in the intake, Color::None if there is no ring
   */
  Color getCurrentRingColor();
private:
  enum State {
    Idle,
    Intaking,
    Outtaking,
    Ejecting,
    EjectStop,
    IntakeLift,
    LiftReverse,
    IntakeMogo
  };
  Destination ringDestination;
  Color filter;
  Color currentRing;
  State currentState;

  double ringStart;
  int ejectTimer = -1;

  pros::Motor intakeMotor;
  pros::Motor hookMotor;
  pros::Optical colorSensor;

  void updateIdle();
  void updateIntaking();
  void updateEjecting();
  void updateEjectStop();
  void updateOuttaking();
  void updateIntakeLift();
  void updateLiftReverse();
  void updateIntakeMogo();
  
  double EJECT_OFFSET = 0.5;
  double LIFT_REVERSE_OFFSET = 0.4;
  double LIFT_OFFSET = -0.2;
  double MOGO_OFFSET = 0.7;
};
