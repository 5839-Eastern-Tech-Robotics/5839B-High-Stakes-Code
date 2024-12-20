#pragma once

#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/adi.hpp"

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

class Intake {
public:
  Intake(pros::Motor intakeMotor, pros::Motor hookMotor, pros::Optical colorSensor, pros::ADIDigitalIn limitSwitch);
  void update();
  void stop();
  void intakeToMogo();
  void intakeToLift();
  void outtake();

  // TODO: intakeOneRing(), mogoOneRing(), liftOneRing()

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
  State currentState;
  Color filter = Color::None;
  Color currentRing;
private:
  Destination ringDestination;

  double ringStart;
  int ejectTimer = -1;

  pros::Motor intakeMotor;
  pros::Motor hookMotor;
  pros::Optical colorSensor;
  pros::ADIDigitalIn limitSwitch;

  void updateIdle();
  void updateIntaking();
  void updateEjecting();
  void updateEjectStop();
  void updateOuttaking();
  void updateIntakeLift();
  void updateLiftReverse();
  void updateIntakeMogo();
  
  double EJECT_OFFSET = 300;
  double LIFT_REVERSE_OFFSET = 0.4;
  double LIFT_OFFSET = -0.2;
  double MOGO_OFFSET = 0.7;
};
