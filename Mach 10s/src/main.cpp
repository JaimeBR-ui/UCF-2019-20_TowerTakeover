// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// Filename: main.cpp

#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::delay(20);
     // Initializes motors and sensors.
     run_display();
     chassis::initialize();
	back_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	front_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	back_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	front_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	lift_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	lift_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	intake_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intake_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
     make_first_path();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	skills();
     //red();
     //blue();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


void opcontrol(void)
{
	// Hold lift down at the start of the match to deploy.
	std::string chassi = "chassi";
	pros::Task chassis(chassis::assign, &chassi, "");

	if (controller_digital(LIFT_SHIFTER_DOWN))
		quick_deploy();

	lift::was_moving = -1;
	while (1)
	{
		lift::assign();
		intake::assign();

		// Set battery voltage.
		lv_bar_set_value(bar1, pros::battery::get_capacity());
		pros::delay(20);
	}

}
