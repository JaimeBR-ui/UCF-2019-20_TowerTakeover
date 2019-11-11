// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

// Set targets in lift.hpp:
//   MIN_POS   LOW_TOWER     HIGH_TOWER  ALLIANCE_TOWER
//   MAX_POS   STACK_HEIGHT  OFF_GROUND  DEPLOY_HEIGHT
// Set targets in intake.hpp:
//   STACK  RELEASE  SCORE

void blue(void)
{

  intake::move_to(SCORE, 127, true);
  pros::delay(2000);
  intake::move_to(RELEASE, 127, true);
  pros::delay(2000);
  intake::move_to(STACK, 127, true);
  pros::delay(2000);
  /*pros::delay(5000);
  chassis::path::make(
    {
      chassis::path::point::startingPoint,
      Point{15_in, 15_in, 90_deg}
    },
    "Test"
  );
  chassis::path::set("Test");
  chassis::path::waitUntilSettled();*/
  //test code

  /*
  pros::Task deploy(deployClaw);
  chassis::path::set("Turn1");
  chassis::path::make(
    {
      Point{0_ft, 0_ft, 0_deg},
      Point{2_ft, -2.3_ft, -90_deg}
    },
    "Turn2"
  );
  chassis::path::waitUntilSettled();
  printf("profiler ended action\n");
  pros::delay(2000);
  chassis::turn(900, 127, 400);
  printf("  turn has ended\n");
  pros::delay(500);
  chassis::path::set("Turn2", false);
  chassis::path::waitUntilSettled();
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  chassis::forward(48, true);
  */
}
