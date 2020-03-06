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
	lift::move_to(DEPLOY_HEIGHT + 400, 127, true);
     intake::move_to(SCORE, 127, false);
     while (abs(SCORE - intake::get_position()) > 230)
          pros::delay(100);
     lift::move_to(0, 127, true);
}

void skills(void)
{
	// Score on tower 1 /////////////////////////////////////////
     chassis::path::set("Straight_10in");
	chassis::path::make(
          {
               point::start,
               Point{21_in, 0_in, 0_deg}
          },
          "Straight_21in"
     );
	chassis::path::wait_until_settled();
     quick_deploy();
     intake::move_to(STACK, 127, true);
	pros::delay(250);
	lift::move_to(LOW_TOWER, 127, true);
     chassis::turn(900, 0, chassis::deployed);

	chassis::path::set("Straight_21in");
	chassis::path::make(
		{
			point::start,
			Point{29_in, 0_in, 0_deg}
		},
		"Straight_29in"
	);
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_21in");
	intake::move_to(RELEASE - 120, 127, false);

	// Score on tower 2 /////////////////////////////////////////
	chassis::path::set("Straight_29in", true);
	pros::delay(250);
	lift::move_to(MIN_POS, 127, false);
	chassis::path::make(
          {
               point::start,
               Point{36_in, 0_in, 0_deg}
          },
          "Straight_36in"
     );
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_29in");
	chassis::turn(-850, 0, chassis::deployed);

	chassis::path::set("Straight_36in");

	chassis::path::make(
          {
               point::start,
               Point{4_in, 0_in, 0_deg}
          },
          "Straight_4in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_36in");

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
               Point{11_in, 0_in, 0_deg}
          },
          "Straight_11in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_10in");
	intake::move_to(RELEASE, 127, true);

	// Score on tower 3.
	chassis::path::set("Straight_11in", true);
	//-------------------------------------------- generate new path here.
	chassis::path::make(
          {
               point::start,
               Point{28_in, 24_in, 0_deg}
          },
          "S_path_1"
     );
	lift::move_to(MIN_POS, 127, true);
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_11in");

	chassis::path::set("S_path_1");
	//-------------------------------------------- generate new path here.
	chassis::path::make(
          {
               point::start,
               Point{48_in, -24_in, 0_deg}
          },
          "S_path_2"
     );
	chassis::path::wait_until_settled();
	chassis::path::remove("S_path_1");

	chassis::path::set("S_path_2");
	chassis::path::make(
		{
			point::start,
			Point{28_in, 0_in, 0_deg}
		},
		"Straight_28in"
	);
	chassis::path::wait_until_settled();
	chassis::path::remove("S_path_2");

	intake::move_to(STACK, 127, true);
	pros::delay(200);
	lift::move_to(LOW_TOWER, 127, false);
	pros::delay(300);
	chassis::path::set("Straight_28in");
	chassis::path::make(
		{
			point::start,
			Point{20_in, 0_in, 0_deg}
		},
		"Straight_20in"
	);
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_28in");

	chassis::path::set("Straight_20in", true);
	chassis::path::make(
		{
			point::start,
			Point{22_in, 0_in, 0_deg}
		},
		"Straight_22in"
	);
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_20in");


	chassis::turn(900, 0, chassis::deployed);
	chassis::path::set("Straight_22in");
	chassis::path::make(
          {
               point::start,
               Point{10_in, 0_in, 0_deg}
          },
          "Straight_10in"
     );
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_22in");

	intake::move_to(SCORE, 127, true);

	// Score on tower 4
	// this may cause errors!!----------------------- !!!
	chassis::path::set("Straight_10in", true);
	chassis::path::make(
          {
               point::start,
			Point{20_in, -13_in, 0_deg}
          },
          "S_Path_3"
     );
	lift::move_to(MIN_POS, 127, false);
	chassis::path::wait_until_settled();
	// this may cause errors!!----------------------- !!!

	chassis::path::set("Straight_10in");
	chassis::path::wait_until_settled();
	intake::move_to(STACK, 127, true);
	pros::delay(200);

	chassis::path::set("Straight_10in", true);
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_10in");

	lift::move_to(LOW_TOWER - 350, 127, true);
	chassis::path::set("S_Path_3");
	chassis::path::make(
		{
			point::start,
			Point{70_in, 0_in, 0_deg}
		},
		"Straight_70in"
	);
	chassis::path::wait_until_settled();

	chassis::path::set("Straight_70in");
	chassis::path::remove("S_Path_3");
	chassis::path::make(
		{
			point::start,
			Point{34_in, 0_in, 0_deg}
		},
		"Straight_34in"
	);
	chassis::path::wait_until_settled();
	intake::move_to(SCORE, 127, true);

	// score on tower 6
	chassis::path::set("Straight_34in", true);
	chassis::path::make(
		{
			point::start,
			Point{30_in, 0_in, 0_deg}
		},
		"Straight_30in"
	);
	lift::move_to(MIN_POS, 127, false);
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_70in");

	chassis::turn(900, 0, chassis::deployed);
	chassis::path::set("Straight_30in");
	chassis::path::make(
		{
			point::start,
			Point{4_in, 0_in, 0_deg}
		},
		"Straight_4in"
	);
	chassis::path::wait_until_settled();
	chassis::path::remove("Straight_30in");

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
