// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

// Set targets in lift.hpp:
//  MIN_POS   LOW_TOWER     HIGH_TOWER  ALLIANCE_TOWER
//  MAX_POS   STACK_HEIGHT  OFF_GROUND  DEPLOY_HEIGHT
// Set targets in intake.hpp:
//  STACK  RELEASE  SCORE

// Notes:
// The boolean in set target makes path to be follwed in reverse
// Boolean in moveTo() defines if program will wait or not.
// In namespace chassis, forward or backward func have their paths removed automatically

void skills(void)
{
  pros::Task deploy(deployClaw);
  chassis::path::set("Straight_6in");
  chassis::path::make(
    {
      point::start,
      Point{24_in, 0_in, 0_deg}
    },
    "Straight_24in"
  );
  chassis::path::waitUntilSettled();
  chassis::path::remove("Straight_6in");
  intake::moveTo(STACK, 127, true);
  lift::moveTo(1700, 127, true);
  chassis::path::set("Straight_24in");
  chassis::path::waitUntilSettled();
  chassis::path::remove("Straight_24in");
  stack();
  chassis::back(21, true); // 21 inches backwards, wait for action
  chassis::turn(-900, 60, 100); // waits by default
  lift::moveTo(STACK_HEIGHT, 127, true);
  chassis::forward(11, true);
  lift::moveTo(0, 127, true);
  pros::delay(700);
  intake::moveTo(SCORE, 127, true);
  chassis::back(11, true);
  // scored first stack
  chassis::turn(900, 127, 400);
  chassis::forward(30, true);
  chassis::turn(900, 127, 400);
  chassis::forward(24, true);
  intake::moveTo(STACK, 127, true);
  lift::moveTo(OFF_GROUND, 127, true);
  chassis::back(52, true);
  chassis::turn(900, 127, 400);
  chassis::forward(9, true); // may want to do an s path instead of straight
  lift::moveTo(2000, 127, true);
  chassis::forward(5, true);
  lift::moveTo(lift::getPosition() - 300, 127, true);
  pros::delay(500);
  intake::moveTo(SCORE, 127, true); // Releases second stack
  chassis::back(5, false);
  // scored second stack
  lift::moveTo(600, 127, true);
  chassis::path::waitUntilSettled();
  chassis::path::make( // make arc from current location to pole or far side
    {
      point::start,
      Point{24_in, 24_in, 90_deg}
    },
    "ArcToPole"
  );
  chassis::path::set("ArcToPole", true);
  chassis::path::waitUntilSettled();
  chassis::path::remove("ArcToPole");
  chassis::turn(900, 127, true);
  chassis::forward(3, true);
  intake::moveTo(STACK, 127, true);
  pros::delay(500);
  lift::moveTo(LOW_TOWER, 127, true);
  chassis::forward(3, true);
  lift::moveTo(lift::getPosition() - 300, 127, true);
  pros::delay(500);
  intake::moveTo(SCORE, 127, true);
  chassis::back(3, false);
  pros::delay(500);
  lift::moveTo(0, 127, true);
  chassis::path::waitUntilSettled();
  //scored on the first tower
}

void makeFirstPath(void)
{ // Creates path as soon as the robot starts the program
  chassis::path::make(
    {
      point::start,
      Point{6_in, 0_in, 0_deg}
    },
    "Straight_6in"
  );
}

void deployClaw(void * ignore)
{ // Thread that deploys the robot's claw
  lift::moveTo(DEPLOY_HEIGHT, 127, true);
  intake::moveTo(SCORE, 127, false);
  while(abs(SCORE - intake::getPosition()) > 230)
    pros::delay(100);
  lift::moveTo(0, 127, true);
}

void stack(void)
{ // Stacks current load on top of a stack and picks up the whole stack
  lift::moveTo(lift::getPosition() - 300, 127, false);
  pros::delay(500);
  intake::moveTo(RELEASE, 127, true); // waits for action to complete
  lift::moveTo(0, 127, true);
  pros::delay(500);
  intake::moveTo(STACK, 127, true);
  lift::moveTo(OFF_GROUND, 127, false);
}

/* Notes
  i think i can make my own isSetteled object for the turn func
  turn is a bit iffy due to my slippery floor causing wheel slippage

*/
