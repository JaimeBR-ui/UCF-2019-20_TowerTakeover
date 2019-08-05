#include "main.h"
/*//values in lift.hpp
for lift
MIN_POS 0 LOW_TOWER 1500  HIGH_TOWER 2200 ALLIANCE_TOWER 700  MAX_POS 3100
for intake
STACK 1000  RELEASE 750 SCORE 500
*/
//raw pointer used since there wont be a memory leak
//I just wanted to use a pointer for sake of consistency with naming(although i
//could have changed the name of the object but) there is no need to use one and
//usually better to avoid them.
//Notes:
//chassis->isSetteled() doesnt work for turns since it doesnt use okapi
//this boolean in set target makes path to be follwed in reverse
//boolean in moveTo() defines if program will wait or not.
//chassis forward or backward movement have their paths removed automatically

void skills(void) {
  /*AsyncMotionProfileController *chassis = &path::profileController;
  path::makeAll("skills");
  chassis->setTarget("Turn1");
  lift::moveTo(LOW_TOWER, 127, false);
  pros::delay(300);
  intake::moveTo(STACK, 127, false);
  chassis->waitUntilSettled();
  path::remove("Turn1");
  path::pathsStored--;
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  chassis->setTarget("Turn2", false);
  chassis->waitUntilSettled();
  path::remove("Turn2");
  path::pathsStored--;
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  chassis::forward(48, true);
  */
  return;
}
