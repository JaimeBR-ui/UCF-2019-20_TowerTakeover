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

     chassis::forward(12, true);
     quick_deploy();
     intake::move_to(STACK, 127, true);
	pros::delay(500);
	lift::move_to(OFF_GROUND, 127, true);
	chassis::back(2, false);
     chassis::turn(900, 0, chassis::deployed);
	chassis::forward(10, true);
	lift::move_to(LOW_TOWER, 127, true);
	chassis::forward(6.5, true);
	intake::move_to(SCORE, 127, true);
	chassis::back(25, false);
	pros::delay(500);
	lift::move_to(MIN_POS, 127, true);
	chassis::path::wait_until_settled();
	chassis::turn(-850, 0, chassis::deployed);
	intake::move_to(RELEASE - 120, 127, true);
	chassis::forward(37, true);
	intake::move_to(STACK, 127, true);
	chassis::back(4, true);
	lift::move_to(LOW_TOWER - 350, 127, true);
	chassis::forward(9, true);
	intake::move_to(SCORE, 127, true);
	chassis::back(4, true);
	intake::move_to(STACK, 127, false);
	chassis::turn(730, 100, chassis::deployed);
	lift::move_to(MIN_POS, 127, true);
	intake::move_to(RELEASE - 200, 127, true);
	chassis::forward(27, false);
	chassis::path::wait_until_settled();
	intake::move_to(STACK, 127, true);
	chassis::back(7, true);
	lift::move_to(MAX_POS - 300, 127, true);
	chassis::forward(10, true);
	pros::delay(500);
	chassis::turn(100, 100, chassis::deployed);
	chassis::forward(3, true);
	pros::delay(2000);
	intake::move_to(SCORE, 127, true);
	chassis::back(6, true);
	lift::move_to(MIN_POS, 127, true);
	chassis::turn(-230, 100, chassis::deployed);
	chassis::back(70, true);
	chassis::forward(30, true);

     /*
     // Score first stack.
     pros::Task deploy(deploy_claw);
     chassis::path::set("Straight_6in");
     chassis::path::make(
          {
               point::start,
               Point{24_in, 0_in, 0_deg}
          },
          "Straight_24in"
     );
     chassis::path::wait_until_settled();
     chassis::path::remove("Straight_6in");
     intake::move_to(STACK, 127, true);
     lift::move_to(1700, 127, true);
     chassis::path::set("Straight_24in");
     chassis::path::wait_until_settled();
     chassis::path::remove("Straight_24in");
     stack();
     // 21 inches backwards, wait for action to complete.
     chassis::back(21, true);
     chassis::turn(-900, 100, 1000); // waits by default
     lift::move_to(STACK_HEIGHT, 127, true);
     chassis::forward(11, true);
     lift::move_to(0, 127, true);
     pros::delay(700);
     intake::move_to(SCORE, 127, true);
     chassis::back(11, true);

     // Score second stack.
     chassis::turn(900, 100, 1000);
     chassis::forward(30, true);
     chassis::turn(900, 100, 1000);
     chassis::forward(24, true);
     intake::move_to(STACK, 127, true);
     lift::move_to(OFF_GROUND, 127, true);
     chassis::back(52, true);
     chassis::turn(900, 100, 1000);
     chassis::forward(9, true); // may want to do an s path instead of straight
     lift::move_to(2000, 127, true);
     chassis::forward(5, true);
     lift::move_to(lift::get_position() - 300, 127, true);
     pros::delay(500);
     intake::move_to(SCORE, 127, true); // Releases second stack
     chassis::back(5, false);

     // Score on tower 1.
     lift::move_to(600, 127, true);
     chassis::path::wait_until_settled();
     chassis::path::make(
          {    // Make arc from current location to pole or far side.
               point::start,
               Point{24_in, 24_in, 90_deg}
          },
          "ArcToPole"
     );
     chassis::path::set("ArcToPole", true);
     chassis::path::wait_until_settled();
     chassis::path::remove("ArcToPole");
     chassis::turn(900, 100, 1000);
     chassis::forward(3, true);
     intake::move_to(STACK, 127, true);
     pros::delay(500);
     lift::move_to(LOW_TOWER, 127, true);
     chassis::forward(3, true);
     lift::move_to(lift::get_position() - 300, 127, true);
     pros::delay(500);
     intake::move_to(SCORE, 127, true);
     chassis::back(3, false);
     pros::delay(500);
     lift::move_to(0, 127, true);
     chassis::path::wait_until_settled();

     // Score on tower 2.*/
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
