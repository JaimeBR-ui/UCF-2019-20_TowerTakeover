// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// Filename: globals.cpp

#include "main.h"

// Motor Declarations.

/*----------------------------------------------------*\
|   Robot                                              |
|                                                      |
|            |-----|     |     |-----|                 |
|            |     |     |     |     |                 |
|            |     |     |     |     |                 |
|            |     |   +---+   |     |                 |
|            |     |   |   |   |     |                 |
|            |     |   |   |   |     |                 |
|            |     | (13) (14) |     |                 |
|            |_____|-|+++++++|-|_____|                 |
|                     \\   \\                          |
|                      \\   \\                         |
|                       +----+                         |
|                 (18)  |    |  (17)                   |
|                       |____|                         |
|                        ///                           |
|                       ///                            |
|                      ///                             |
|                  +--|  |------+                      |
|   Right   (12)  /   |  |     /  (20)    Left         |
|          (11)  /    |  |    /  (19)                  |
|               +------------+                         |
|                   Front                              |
\*----------------------------------------------------*/
// new clawR: 5
// new clawL: 16
// Drive.
pros::Motor front_left(19, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor front_right(11, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor back_right(12, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor back_left(20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

// Lift.
pros::Motor lift_right(18, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor lift_left(17, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);

// Intake.
pros::Motor intake_right(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intake_left(16, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);


// Controller Functions.
pros::Controller controller(pros::E_CONTROLLER_MASTER);

std::int32_t controller_digital(pros::controller_digital_e_t channel)
{
     return controller.get_digital(channel);
}

std::int32_t controller_analog(pros::controller_analog_e_t channel)
{
  return controller.get_analog(channel);
}
