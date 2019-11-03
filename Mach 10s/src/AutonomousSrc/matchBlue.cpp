// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

void blue(void)
{
     chassis::path::make({
         point::start,
         Point{24_in, 24_in, 90_deg}
       },
       "Test"
     );
     chassis::path::set("Test");
     chassis::path::wait_until_settled();
  chassis::turn(900, 100, 1000);
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
