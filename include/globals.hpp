#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pid.hpp"
#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"

extern pros::Controller controller;
 
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
 
extern lemlib::OdomSensors sensors;
 
extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve steerCurve;

extern lemlib::Chassis chassis;
extern lemlib::Chassis chassisPTO;
