#include "globals.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/rotation.hpp"
#include "robot/subsytems/chassis.hpp"
#include "robot/subsytems/intake.hpp"
#include "pros/optical.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Optical colorSensor(11);
pros::adi::DigitalIn ringSwitch('F');

pros::Motor intakeMotor(-12);
pros::Motor intakeHookMotor(6);

// USE GET_VALUE
pros::adi::Potentiometer ladybrownPot('D', pros::E_ADI_POT_EDR);
pros::MotorGroup ladybrown({17, -20}, pros::MotorGearset::blue);
lemlib::PID ladybrownPID(1, 0, 5); // TODO: TUNE THIS WJAT

pros::adi::Pneumatics clamp('H', false);
pros::adi::Pneumatics PTO('G', false);
pros::adi::Pneumatics deringer('E', false);

pros::MotorGroup leftMotors({17, 16, -15}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({-20, -19, 18}, pros::MotorGearset::blue);

pros::MotorGroup leftMotorsPTO({16, -15}, pros::MotorGearset::blue);
pros::MotorGroup rightMotorsPTO({-19, 18}, pros::MotorGearset::blue);

lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    15.6,
    lemlib::Omniwheel::OLD_325,
    400,
    2
);

lemlib::Drivetrain drivetrainPTO(
    &leftMotorsPTO,
    &rightMotorsPTO,
    15.6,
    lemlib::Omniwheel::OLD_325,
    400,
    2
);

lemlib::ControllerSettings linearController(
    // 10, 3
    10,
    0,
    3,
    3,
    1,
    100,
    3,
    500,
    20
);

lemlib::ControllerSettings angularController(
    // 2, 10
    6,
    0,
    30,
    3,
    1,
    100,
    3,
    500,
    0
);

pros::Rotation horizontalSensor(13);
pros::Rotation verticalSensor(14);
pros::Imu imu(8);

lemlib::TrackingWheel horizontalPod(
    &horizontalSensor,
    lemlib::Omniwheel::NEW_2,
    2.5
);

lemlib::TrackingWheel verticalPod(
    &verticalSensor,
    lemlib::Omniwheel::NEW_2,
    3
);

lemlib::OdomSensors sensors(
    &verticalPod,
    nullptr,
    &horizontalPod,
    nullptr,
    &imu
);

lemlib::ExpoDriveCurve throttleCurve(
    3,
    10,
    1.019
);

lemlib::ExpoDriveCurve steerCurve(
    3,
    10,
    1.019
);

lemlib::Chassis m6(
    drivetrain, 
    linearController, 
    angularController, 
    sensors, 
    &throttleCurve, 
    &steerCurve
);

lemlib::Chassis m4(
    drivetrainPTO,
    linearController,
    angularController,
    sensors,
    &throttleCurve,
    &steerCurve
);

class Intake intake(intakeMotor, intakeHookMotor, colorSensor, ringSwitch);
Chassis chassis(&m6, &m4, PTO, &ladybrown, ladybrownPot, ladybrownPID);