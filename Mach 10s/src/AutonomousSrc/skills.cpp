// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

// Set targets in lift.hpp:
//   MIN_POS   LOW_TOWER     HIGH_TOWER  ALLIANCE_TOWER
//   MAX_POS   STACK_HEIGHT  OFF_GROUND  DEPLOY_HEIGHT
// Set targets in intake.hpp:
//   STACK  RELEASE  SCORE

// Notes:
// The boolean in set target makes path to be follwed in reverse.
// Boolean in move_to() defines if program will wait or not.
// In namespace chassis, forward or backward functions have
// their paths removed automatically if they are set to wait

void quick_deploy(void)
{
	lift::move_to(DEPLOY_HEIGHT + 300, 127, true);
     intake::move_to(SCORE, 127, false);
     while (abs(SCORE - intake::get_position()) > 230)
          pros::delay(100);
     lift::move_to(0, 127, true);
}

void skills(void)
{
     // chassis::forward(12, true);
     // quick_deploy();
     // intake::move_to(STACK, 127, true);
	// pros::delay(500);
	// lift::move_to(OFF_GROUND, 127, true);
	// chassis::back(2, false);
     // chassis::turn(900, 0, chassis::deployed);
	// chassis::forward(10, true);
	// lift::move_to(LOW_TOWER, 127, true);
	// chassis::forward(6.5, true);
	// intake::move_to(SCORE, 127, true);
	//
	// // Score on tower 2.
	// chassis::back(25, false);
	// pros::delay(500);
	// lift::move_to(MIN_POS, 127, true);
	// chassis::path::wait_until_settled();
	// chassis::turn(-850, 0, chassis::deployed);
	// intake::move_to(RELEASE - 120, 127, true);
	// chassis::forward(37, true);
	// intake::move_to(STACK, 127, true);
	// chassis::back(4, true);
	// lift::move_to(LOW_TOWER - 350, 127, true);
	// chassis::forward(9, true);
	// intake::move_to(SCORE, 127, true);

	// Score on tower 3.
	quick_deploy();// for home prog.
	chassis::back(4, true);
	intake::move_to(STACK, 127, false);
	chassis::turn(800, 100, chassis::deployed);
	chassis::path::make(
		{
			point::start,
			Point{24_in, 10_in, 0_deg}
		},
		"SCurve"
	);
	chassis::path::set("SCurve");
	chassis::path::wait_until_settled();
	intake::move_to(STACK, 127, true);
	chassis::back(7, true);
	lift::move_to(MAX_POS - 300, 127, true);
	chassis::forward(10, true);
	pros::delay(1000);
	intake::move_to(SCORE, 127, true);
	chassis::back(6, true);
	lift::move_to(MIN_POS, 127, true);
	chassis::turn(-800, 0, chassis::deployed);
	// chassis::forward(75, true);
	//
	// // Score on tower 4
	// chassis::back(20, true);
	// chassis::turn(900, 0, chassis::deployed);
	// chassis::forward(24, true);
	// intake::move_to(STACK, 127, true);
	// chassis::back(4, true);
	// lift::move_to(LOW_TOWER - 350, 127, true);
	// chassis::forward(9, true);
	// intake::move_to(SCORE, 127, true);
	// chassis::back(4, true);
	//
	// // maybe go back and get the 4 stack.

}

void make_first_path(void)
{    // Creates path as soon as the robot starts the program.
     chassis::path::make(
          {
               point::start,
               Point{6_in, 0_in, 0_deg}
          },
          "Straight_6in"
     );
}

void deploy_claw(void * ignore)
{    // Thread that deploys the robot's claw.
     lift::move_to(DEPLOY_HEIGHT, 127, true);
     intake::move_to(SCORE, 127, false);
     while (abs(SCORE - intake::get_position()) > 230)
          pros::delay(100);
     lift::move_to(0, 127, true);
}

void stack(void)
{    // Stacks current load on top of a stack and picks up the whole stack.
     lift::move_to(lift::get_position() - 300, 127, false);
     pros::delay(500);
     intake::move_to(RELEASE, 127, true); // Waits for action.
     lift::move_to(0, 127, true);
     pros::delay(500);
     intake::move_to(STACK, 127, true);
     lift::move_to(OFF_GROUND, 127, false);
}

/* Notes
i think i can make my own isSetteled object for the turn func
turn is a bit iffy due to my slippery floor causing wheel slippage
*/
