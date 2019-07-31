#include "main.h"

//raw pointer used since there wont be a memory leak
//I just wanted to use a pointer for sake of consistency with naming
//there is no need to use one and usually better to avoid them

void skills(void) {
  path::makePaths();
  AsyncMotionProfileController *chassis = &path::profileController;
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
