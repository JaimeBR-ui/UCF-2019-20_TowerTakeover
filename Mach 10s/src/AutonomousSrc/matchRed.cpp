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
     chassis::path::set("Straight_4in");
     chassis::path::make(
          {
               point::start,
               Point{6_in, 0_in, 0_deg}
          },
          "Straight_6in"
     );
     // Do not remove this one.
	chassis::path::wait_until_settled();

	quick_deploy();
	intake::move_to(STACK, 127, true);
	pros::delay(500);
	lift::move_to(OFF_GROUND + 600, 127, true);
     chassis::path::set("Straight_6in");
     chassis::path::make(
          {
               point::start,
               Point{4_in, 0_in, 0_deg}
          },
          "Straight_4in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_6in");
     lift::move_to(OFF_GROUND + 300, 120, false);
     pros::delay(500);
	intake::move_to(SCORE, 127, true);
	lift::move_to(MIN_POS, 127, true);
	intake::move_to(STACK, 127, true);
	pros::delay(200);
	lift::move_to(OFF_GROUND + 100, 127, true);
     chassis::path::set("Straight_4in");
     chassis::path::make(
          {
               point::start,
               Point{16_in, 0_in, 0_deg}
          },
          "Straight_16in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_4in");

	chassis::turn(-950, 0, chassis::deployed);
	lift::move_to(OFF_GROUND + 600, 127, true);
     chassis::path::set("Straight_16in");
     chassis::path::make(
          {
               point::start,
               Point{15_in, 0_in, 0_deg}
          },
          "Straight_15in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_16in");

	lift::move_to(OFF_GROUND + 300, 120, false);
     pros::delay(500);
	intake::move_to(SCORE, 127, true);
	lift::move_to(MIN_POS, 127, true);
	intake::move_to(STACK, 127, true);
     pros::delay(700);
	lift::move_to(OFF_GROUND + 300, 127, true);
     pros::delay(200);
     chassis::forward(5, true);
	chassis::path::wait_until_settled();
     // Do not remove this one.

     // Turn and score in the zone.
     chassis::turn(-450, 0, chassis::deployed);
     chassis::path::set("Straight_15in");
     chassis::path::make(
          {
               point::start,
               Point{14_in, 0_in, 0_deg}
          },
          "Straight_14in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_15in");

	lift::move_to(MIN_POS, 127, true);
     pros::delay(500);
	intake::move_to(SCORE, 127, true);
     chassis::path::set("Straight_14in", true);
     chassis::path::make(
          {
               point::start,
               Point{24_in, 0_in, 0_deg}
          },
          "Straight_24in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_14in");

     // Align with wall.
	chassis::turn(450, 0, chassis::deployed);
	lift::move_to(OFF_GROUND + 800, 127, true);
     chassis::path::set("Straight_24in");
     chassis::path::make(
          {
               point::start,
               Point{42_in, 0_in, 0_deg}
          },
          "Straight_42in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_24in");

     // Go to 4 stack.
     chassis::path::set("Straight_42in", true);
     chassis::path::make(
          {
               point::start,
               Point{17_in, 0_in, 0_deg}
          },
          "Straight_17in"
     );

	pros::delay(500);
	lift::move_to(MIN_POS, 127, true);
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_42in");

	chassis::turn(900, 0, chassis::deployed);
     chassis::path::set("Straight_17in");
     chassis::path::make(
          {
               point::start,
               Point{11_in, 0_in, 0_deg}
          },
          "Straight_11in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_17in");

     intake::move_to(STACK, 127, true);
     pros::delay(500);
     lift::move_to(OFF_GROUND + 300, 127, true);
     chassis::path::set("Straight_11in");
     chassis::path::make(
          {
               point::start,
               Point{37_in, 0_in, 0_deg}
          },
          "Straight_37in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_11in");

     chassis::turn(-1350, 0, chassis::deployed);
     chassis::path::set("Straight_37in");
     chassis::path::make(
          {
               point::start,
               Point{12_in, 0_in, 0_deg}
          },
          "Straight_12in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_37in");
     lift::move_to(LOW_TOWER, 127, true);
     chassis::path::set("Straight_12in");
     chassis::path::make(
          {
               point::start,
               Point{30_in, 0_in, 0_deg}
          },
          "Straight_30in"
     );
	chassis::path::wait_until_settled();
     chassis::path::remove("Straight_12in");
     pros::delay(600);
     lift::move_to(LOW_TOWER - 600, 120, false);
     pros::delay(700);
     intake::move_to(SCORE, 127, true);

     // Reset lift position.
     chassis::path::set("Straight_30in", true);
     pros::delay(600);
     lift::move_to(MIN_POS, 127, true);
     chassis::path::wait_until_settled();
     chassis::path::remove("Straight_30in");

}

void get_last3(void) {}
