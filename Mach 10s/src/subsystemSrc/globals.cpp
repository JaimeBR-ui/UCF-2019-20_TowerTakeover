// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

using namespace okapi;

//Motor Declarations

//Drive
pros::Motor front_left(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor front_right(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor back_right(9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor back_left(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

//Lift
pros::Motor lift_right(3, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor lift_left(8, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);

//Intake
pros::Motor intake_right(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intake_left(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);


//Controller Functions
pros::Controller controller(pros::E_CONTROLLER_MASTER);

std::int32_t controller_digital(pros::controller_digital_e_t channel)
{
     return controller.get_digital(channel);
}

std::int32_t controller_analog(pros::controller_analog_e_t channel)
{
  return controller.get_analog(channel);
}
