#include "main.h"

using namespace okapi;

//Motor Declarations

//Drive
pros::Motor driveLeftFront(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

//Lift
pros::Motor liftRight(3, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor liftLeft(6, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);

//Intake
pros::Motor intakeRight(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeLeft(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);


//Controller Functions
pros::Controller controller(pros::E_CONTROLLER_MASTER);

std::int32_t controllerDigital(pros::controller_digital_e_t channel) {
  return controller.get_digital(channel);
}

std::int32_t controllerAnalog(pros::controller_analog_e_t channel) {
  return controller.get_analog(channel);
}
