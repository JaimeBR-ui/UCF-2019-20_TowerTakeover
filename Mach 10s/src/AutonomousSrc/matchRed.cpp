// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// Filename: matchRed.cpp

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

void get_last3(void);

void red(void)
{
     chassis::forward(4, true);
	quick_deploy();
	intake::move_to(STACK, 127, true);
	pros::delay(500);
	lift::move_to(OFF_GROUND + 600, 127, true);
	chassis::forward(6, true);
	intake::move_to(SCORE, 127, true);
	lift::move_to(MIN_POS, 127, true);
	intake::move_to(STACK, 127, true);
	pros::delay(200);
	lift::move_to(OFF_GROUND + 100, 127, true);
	chassis::forward(3, true);

	chassis::turn(-900, 0, chassis::deployed);
	lift::move_to(OFF_GROUND + 600, 127, true);
	chassis::forward(16, true);
	intake::move_to(SCORE, 127, true);
     pros::delay(600);
	lift::move_to(MIN_POS, 127, true);
	intake::move_to(STACK, 127, true);
	lift::move_to(OFF_GROUND + 200, 127, true);
     pros::delay(500);
	chassis::forward(4, true);

     // Turn and score in the zone.
     chassis::turn(-450, 0, chassis::deployed);
	chassis::forward(15, true);
	lift::move_to(MIN_POS, 127, true);
	intake::move_to(SCORE, 127, true);
	chassis::back(14, true);

     // Align with wall.
	chassis::turn(450, 0, chassis::deployed);
	lift::move_to(LOW_TOWER - 100, 127, true);
     intake::move_to(200, 127, true); // only here for testing.
	chassis::forward(12, true);

     // Go to 4 stack.
	chassis::back(48, false);
	pros::delay(500);
     intake::move_to(SCORE, 127, false); // oly here for testing
	lift::move_to(MIN_POS, 127, true);
	chassis::path::wait_until_settled();
	chassis::turn(900, 0, chassis::deployed);
	chassis::forward(19, true);
     intake::move_to(STACK, 127, true);
     chassis::turn(-1350, 0, chassis::deployed);
     chassis::forward(40, true);
     lift::move_to(LOW_TOWER, 127, true);
     chassis::forward(5, true);
     intake::move_to(RELEASE, 127, true);
     pros::delay(500);
     intake::move_to(SCORE, 127, true);

     // Reset lift position.
     chassis::back(20, false);
     pros::delay(600);
     lift::move_to(MIN_POS, 127, true);
     chassis::path::wait_until_settled();
}

void get_last3(void) {}
