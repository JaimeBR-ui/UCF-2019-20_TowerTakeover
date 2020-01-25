// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// Filename: skills.cpp

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
     chassis::path::set("Straight_10in");
	chassis::path::wait_until_settled();
     quick_deploy();
     intake::move_to(STACK, 127, true);
	pros::delay(500);
	lift::move_to(OFF_GROUND, 127, true);
     chassis::turn(900, 0, chassis::deployed);
	chassis::forward(13, true);
	lift::move_to(LOW_TOWER, 127, true);
	chassis::forward(6.5, true);
	intake::move_to(SCORE, 127, true);

	// Score on tower 2.
	chassis::back(27, false);
	pros::delay(400);
	lift::move_to(MIN_POS, 127, false);
	chassis::path::make(
          {
               point::start,
               Point{37_in, 0_in, 0_deg}
          },
          "Straight_37in"
     );
	chassis::path::wait_until_settled();
	chassis::turn(-850, 0, chassis::deployed);

	chassis::path::set("Straight_37in");
	intake::move_to(RELEASE - 120, 127, false);
	chassis::path::make(
          {
               point::start,
               Point{4_in, 0_in, 0_deg}
          },
          "Straight_4in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_37in");

	intake::move_to(STACK, 127, true);
	chassis::path::set("Straight_4in", true);
	chassis::path::make(
          {
               point::start,
               Point{10_in, 0_in, 0_deg}
          },
          "Straight_10in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_4in");

	lift::move_to(LOW_TOWER - 350, 127, true);
	chassis::path::set("Straight_10in");
	chassis::path::make(
          {
               point::start,
               Point{8_in, 0_in, 0_deg}
          },
          "Straight_8in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_10in");
	intake::move_to(SCORE, 127, true);

	// Score on tower 3.
	chassis::path::set("Straight_8in", true);
	chassis::path::make(
          {
               point::start,
               Point{27_in, 0_in, 0_deg}
          },
          "Straight_27in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_8in");

	intake::move_to(STACK, 127, false);
	chassis::turn(700, 0, chassis::deployed);
	lift::move_to(MIN_POS, 127, true);
	intake::move_to(RELEASE - 200, 127, true);

	chassis::path::set("Straight_27in");
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_27in");

	intake::move_to(STACK, 127, true);
	pros::delay(200);
	lift::move_to(OFF_GROUND, 127, true);
	chassis::back(6, true);
	lift::move_to(MAX_POS - 300, 127, true);

	chassis::turn(120, 35, chassis::deployed_1cube);

	chassis::forward(10, true);
	pros::delay(2000);
	intake::move_to(SCORE, 127, true);
	chassis::back(8, true);
	pros::delay(1200);
	lift::move_to(OFF_GROUND + 800, 127, true);
	chassis::turn(-840, 0, chassis::deployed);
	intake::move_to(STACK, 127, true);

	// // Score on tower 4.
	chassis::forward(80, true);
	chassis::back(22, true);
	chassis::turn(900, 0, chassis::deployed);
	intake::move_to(SCORE, 127, false);
	lift::move_to(MIN_POS, 127, true);
	chassis::forward(8, true);
	intake::move_to(STACK, 127, true);
	chassis::back(8, true);
	lift::move_to(LOW_TOWER, 127, true);
	chassis::forward(13, true);
	intake::move_to(SCORE, 127, true);
	chassis::back(24, true);
	// // maybe go back and get the 4 stack.

}

void make_first_path(void)
{    // Creates path as soon as the robot starts the program.
     chassis::path::make(
          {
               point::start,
               Point{10_in, 0_in, 0_deg}
          },
          "Straight_10in"
     );
	chassis::path::make(
          {
               point::start,
               Point{4_in, 0_in, 0_deg}
          },
          "Straight_4in"
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
