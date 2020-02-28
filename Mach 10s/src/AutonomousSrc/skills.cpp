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
	chassis::path::make(
          {
               point::start,
               Point{13_in, 0_in, 0_deg}
          },
          "Straight_37in"
     );
	chassis::path::wait_until_settled();
     quick_deploy();
     intake::move_to(STACK, 127, true);
	pros::delay(500);
	lift::move_to(OFF_GROUND, 127, true);
     chassis::turn(900, 0, chassis::deployed);

	chassis::path::set("Straight_13in");
	chassis::path::make(
		{
			point::start,
			Point{8_in, 0_in, 0_deg}
		},
		"Straight_8in"
	);
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_13in");

	lift::move_to(LOW_TOWER, 127, true);
	chassis::path::set("Straight_8in");
	chassis::path::make(
          {
               point::start,
               Point{29_in, 0_in, 0_deg}
          },
          "Straight_29in"
     );
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_8in");

	intake::move_to(SCORE, 127, true);

	// Score on tower 2.
	chassis::path::set("Straight_29in", true);
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
	chassis::path::remove("Straight_29in");
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
	chassis::path::make(
          {
               point::start,
               Point{6_in, 0_in, 0_deg}
          },
          "Straight_6in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_27in");

	intake::move_to(STACK, 127, true);
	pros::delay(200);
	lift::move_to(OFF_GROUND, 127, true);
	chassis::path::set("Straight_6in", true);
	chassis::path::make(
          {
               point::start,
               Point{10_in, 0_in, 0_deg}
          },
          "Straight_10in"
     );
	chassis::path::wait_until_settled();

	lift::move_to(MAX_POS - 300, 127, true);

	chassis::turn(100, 38, chassis::deployed_1cube);

	chassis::path::set("Straight_10in");
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_10in");

	pros::delay(2000);
	intake::move_to(SCORE, 127, true);
	chassis::path::set("Straight_6in", true);
	//-------------------------------------------- generate new path here.
	chassis::path::make(
          {
               point::start,
               Point{30_in, 0_in, 0_deg},
			Point{55_in, 19_in, 0_deg}
          },
          "S_path_1"
     );
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_6in");
	pros::delay(1200);
	lift::move_to(MIN_POS, 127, true);
	chassis::turn(-820, 0, chassis::deployed);
	intake::move_to(SCORE, 127, true);

	// score on tower 4
	chassis::path::set("S_path_1");
	chassis::path::make(
          {
               point::start,
               Point{23_in, 0_in, 0_deg}
          },
          "Straight_23in"
     );
	chassis::path::wait_until_settled();
	chassis::path::remove("S_path_1");
	intake::move_to(STACK, 127, true);
	pros::delay(300);
	chassis::turn(900, 0, chassis::deployed);
	lift::move_to(LOW_TOWER, 127, true);
	chassis::path::set("Straight_23in");
	chassis::path::make(
          {
               point::start,
               Point{8_in, 0_in, 0_deg}
          },
          "Straight_8in"
     );
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_23in");
	intake::move_to(SCORE, 127, true);
	chassis::path::set("Straight_8in", true);
	chassis::path::wait_until_settled();
	lift::move_to(MIN_POS, 127, true);

	chassis::path::set("Straight_8in");
	chassis::path::wait_until_settled();

	intake::move_to(SCORE, 127, true);
	chassis::path::set("Straight_8in", true);
	//-------------------------------------------- generate new path here.
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_8in");

	// score on tower 5


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
