#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "pros/motor_group.hpp"
#include <map>

class Chassis {
enum ChassisStates {
    PTORetractedEmpty,
    PTOExtendedEmpty,
    PTORetractedMogo,
    PTOExtendedMogo,
    PTORetractedMogo4Rings,
    PTOExtendedMogo4Rings,
    PTORetracted8Rings,
    PTOExtended8Rings
};

struct ChassisConfig {
    pros::MotorGroup leftMotors;
    pros::MotorGroup rightMotors;
    lemlib::ControllerSettings linearController;
    lemlib::ControllerSettings angularController;
    lemlib::Chassis chassis;
};

public:
    Chassis();
    static Chassis instance;
    lemlib::Chassis chassis();
    ChassisStates chassisState();

private:
    std::map<ChassisStates, ChassisConfig> chassies;
};
