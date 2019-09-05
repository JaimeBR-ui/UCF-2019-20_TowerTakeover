#include "main.h"

/*
set targets in lift.hpp
  MIN_POS LOW_TOWER  HIGH_TOWER ALLIANCE_TOWER MAX_POS
set targets in intake.hpp
  STACK RELEASE SCORE
*/

// Notes:
// chassis->isSetteled() doesnt work for turns since it doesnt use okapi, unless...
// the boolean in set target makes path to be follwed in reverse
// boolean in moveTo() defines if program will wait or not.
// in namespace chassis, forward or backward func have their paths removed automatically

void deployClaw(void * ignore);
void stack(void);

void skills(void)
{
  pros::Task deploy(deployClaw);
  chassis::path::set("Straight_24in");
  chassis::path::make({
      point::start,
      Point{6_in, 0_in, 0_deg}
    },
    "Straight_6in"
  );
  chassis::path::waitUntilSettled();
  chassis::path::remove("Straight_24in");
  chassis::path::set("Straight_6in");
  chassis::path::waitUntilSettled();
  chassis::path::remove("Straight_6in");
  intake::moveTo(STACK, 127, true); // waits for action to complete
  lift::moveTo(ALLIANCE_TOWER - 300, 127, false);
  pros::delay(100);
  chassis::back(21, true); // 21 inches backwards, wait for action
  chassis::turn(900, 60, 100); // waits by default
  lift::moveTo(ALLIANCE_TOWER + 400, 127, true);
  chassis::forward(20, true);
  stack();
  chassis::forward(9, true);
  chassis::turn(450, 60, 400);
  chassis::forward(11, true);
  lift::moveTo(0, 127, true);
  pros::delay(700);
  intake::moveTo(SCORE, 127, true);
  chassis::back(11, true);
}

void makeFirstPath(void)
{
  chassis::path::make({
      point::start,
      Point{24_in, 0_in, 0_deg}
    },
    "Straight_24in"
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
{
  lift::moveTo(ALLIANCE_TOWER - 300, 127, false);
  pros::delay(500);
  intake::moveTo(RELEASE, 127, true); // waits for action to complete
  lift::moveTo(0, 127, true);
  pros::delay(500);
  intake::moveTo(STACK, 127, true);
  lift::moveTo(ALLIANCE_TOWER - 300, 127, false);
}

/* Notes
  i think i can make my own isSetteled object for the turn func
  turn is a bit iffy due to my slippery floor causing wheel slippage
*/
