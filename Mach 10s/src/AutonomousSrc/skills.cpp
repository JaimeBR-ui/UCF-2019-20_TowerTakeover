#include "main.h"

using namespace path;

void skills(void) {
  path::makePaths();
  //raw pointer used since there wont be a memory leak
  AsyncMotionProfileController *chassis = &profileController;
  chassis->setTarget("Turn1");
  chassis->waitUntilSettled();
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  chassis->setTarget("Turn2", false);
  //this boolean if true, ↑, makes path to be follwed backwards/reverse
  chassis->waitUntilSettled();
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  chassis::forward(48, true);
  chassis = NULL;
  delete(chassis);
  return;
}
