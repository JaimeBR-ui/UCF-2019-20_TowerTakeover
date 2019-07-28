#include "main.h"

using namespace path;

void skills(void) {
  path::makePaths();
  path::setPath("Turn1");
  path::waitUntilSettled();
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  path::setPath("Turn2");
  path::waitUntilSettled();
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  path::setPath("Straight4");
  path::waitUntilSettled();
  path::makePath({startingPoint, makePoint(1,1,0)}, "Straight1");
  return;
}
