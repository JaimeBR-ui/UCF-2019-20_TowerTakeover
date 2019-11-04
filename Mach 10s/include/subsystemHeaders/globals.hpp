// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

// Definitions.
#define LEFT_JOYSTICK pros::E_CONTROLLER_ANALOG_LEFT_Y
#define RIGHT_JOYSTICK pros::E_CONTROLLER_ANALOG_RIGHT_Y
#define INTAKE pros::E_CONTROLLER_DIGITAL_L2
#define OUTTAKE pros::E_CONTROLLER_DIGITAL_L1
#define LIFT_SHIFTER_UP pros::E_CONTROLLER_DIGITAL_R2
#define LIFT_SHIFTER_DOWN pros::E_CONTROLLER_DIGITAL_R1
#define A pros::E_CONTROLLER_DIGITAL_A
#define B pros::E_CONTROLLER_DIGITAL_B
#define X pros::E_CONTROLLER_DIGITAL_X
#define Y pros::E_CONTROLLER_DIGITAL_Y
#define DOWN pros::E_CONTROLLER_DIGITAL_DOWN
#define DEPLOY_HEIGHT 400

// Controller.
extern pros::Controller controller;
std::int32_t controller_digital(pros::controller_digital_e_t channel);
std::int32_t controller_analog(pros::controller_analog_e_t channel);

// PID struct
struct Gains
{
     double Kp;
     double Ki;
     double Kd;
};

// Motors.
extern pros::Motor back_left;
extern pros::Motor front_left;
extern pros::Motor back_right;
extern pros::Motor front_right;
extern pros::Motor intake_right;
extern pros::Motor intake_left;
extern pros::Motor lift_left;
extern pros::Motor lift_right;
