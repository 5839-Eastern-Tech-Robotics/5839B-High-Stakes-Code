#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include <map>

class Chassis {
enum ChassisStates {
    PTORetractedEmpty,
    PTOExtendedEmpty,
    // PTORetractedMogo,
    // PTOExtendedMogo,
    // PTORetractedMogo4Rings,
    // PTOExtendedMogo4Rings,
    // PTORetracted8Rings,
    // PTOExtended8Rings
};

struct ChassisConfig {
    pros::MotorGroup leftMotors;
    pros::MotorGroup rightMotors;
    lemlib::ControllerSettings linearController;
    lemlib::ControllerSettings angularController;
    lemlib::Chassis chassis;
};

public:
    Chassis(ChassisConfig m4, ChassisConfig m6, )

private:
    ChassisConfig m6;
    ChassisConfig m4;
    pros::adi::Pneumatics pto;
    pros::MotorGroup ladybrown;
};
