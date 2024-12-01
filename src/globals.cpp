#include "globals.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Motor intakeMotor(-12);
pros::Motor intakeHookMotor(9);

pros::MotorGroup intakeLiftMotor({5, -3}, pros::MotorGearset::blue);
lemlib::PID liftController(2, 0, 10);
float intakeLiftSetPoint = 0;

pros::adi::Pneumatics clamp('H', true);
pros::adi::Pneumatics PTO('G', false);

pros::MotorGroup leftMotors({17, 16, -15}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({-20, -19, 18}, pros::MotorGearset::blue);

pros::MotorGroup leftMotorsPTO({16, -15}, pros::MotorGearset::blue);
pros::MotorGroup rightMotorsPTO({-19, 18}, pros::MotorGearset::blue);

lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              15.6, // track width
                              lemlib::Omniwheel::OLD_325,
                              400,
                              2
);

lemlib::Drivetrain drivetrainPTO(&leftMotorsPTO,
                              &rightMotorsPTO,
                              15.6,
                              lemlib::Omniwheel::OLD_325,
                              400,
                              2
);

lemlib::ControllerSettings linearController(10,
                                            0,
                                            3,
                                            3,
                                            1,
                                            100,
                                            3,
                                            500,
                                            20
);

lemlib::ControllerSettings angularController(2,
                                             0,
                                             10,
                                             3,
                                             1,
                                             100,
                                             3,
                                             500,
                                             0
);

lemlib::OdomSensors sensors(nullptr,
                            nullptr,
                            nullptr,
                            nullptr,
                            nullptr
);

lemlib::ExpoDriveCurve throttleCurve(3,
                                     10,
                                     1.019
);

lemlib::ExpoDriveCurve steerCurve(3,
                                  10,
                                  1.019
);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);
lemlib::Chassis chassisPTO(drivetrainPTO, linearController, angularController, sensors, &throttleCurve, &steerCurve);
