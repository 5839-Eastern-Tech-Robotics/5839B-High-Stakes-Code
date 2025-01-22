#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "lemlib/pid.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "robot/subsytems/intake.hpp"

extern pros::Controller controller;

extern pros::Optical colorSensor;
extern pros::adi::DigitalIn ringSwitch;
 
extern pros::Motor intakeMotor;
extern pros::Motor intakeHookMotor;

extern pros::MotorGroup intakeLiftMotor;
extern lemlib::PID liftController;
extern float intakeLiftSetPoint;
 
extern pros::adi::Pneumatics clamp;
extern pros::adi::Pneumatics PTO;
 
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;
 
extern pros::MotorGroup leftMotorsPTO;
extern pros::MotorGroup rightMotorsPTO;
 
extern lemlib::Drivetrain drivetrain;
extern lemlib::Drivetrain drivetrainPTO;
 
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;
 
extern pros::Rotation horizontalSensor;
extern pros::Rotation verticalSensor;
extern pros::Imu imu;

extern lemlib::TrackingWheel horizontalPod;
extern lemlib::TrackingWheel verticalPod;

extern lemlib::OdomSensors sensors;
 
extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve steerCurve;

extern lemlib::Chassis chassis;
extern lemlib::Chassis chassisPTO;

extern Intake intake;
