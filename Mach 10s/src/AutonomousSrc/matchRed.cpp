// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

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

     // Align with scoring zone.
     chassis::turn(-450, 0, chassis::deployed);
	chassis::forward(15, true);
	lift::move_to(MIN_POS, 127, true);
	intake::move_to(SCORE, 127, true);
	chassis::back(14, true);

     // Align with wall.
	chassis::turn(450, 0, chassis::deployed);
	lift::move_to(LOW_TOWER, 127, true);
	chassis::forward(12, true);

     // Go to 4 stack.
	chassis::back(48, false);
	pros::delay(500);
	lift::move_to(MIN_POS, 127, true);
	chassis::path::wait_until_settled();
	chassis::turn(900, 0, chassis::deployed);
	chassis::forward(18, true);

}

void get_last3(void)
{
	intake::move_to(SCORE, 127, true);
	chassis::forward(26, true);
	intake::move_to(STACK, 127, true);
	lift::move_to(OFF_GROUND, 127, true);
	chassis::back(8, true);
	chassis::turn(1350, 0, chassis::deployed);
	chassis::forward(23, true);
	lift::move_to(MAX_POS, 127, true);
	chassis::forward(5, true);
	lift::move_to(MAX_POS - 200, 127, true);
	intake::move_to(RELEASE, 127, true);
	pros::delay(750);
	intake::move_to(SCORE, 127, true);
	chassis::back(24, false);
	lift::move_to(MIN_POS, 127, true);
	chassis::path::wait_until_settled();
}
