#include "main.h"

using namespace path;

void skills(void) {
  path::makePaths();
  path::setPath("Turn1");
  path::waitUntilSettled();
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  path::setPath("Turn2", false);
  //this boolean if true, ↑, makes path to be follwed backwards/reverse
  path::waitUntilSettled();
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  chassis::forward(48, true);
  return;
}
