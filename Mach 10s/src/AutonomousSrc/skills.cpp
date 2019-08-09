#include "main.h"
/*
//values in lift.hpp
for lift
MIN_POS LOW_TOWER  HIGH_TOWER ALLIANCE_TOWER MAX_POS
for intake
//values in intake.hpp
STACK RELEASE SCORE
*/
//raw pointer used since there wont be a memory leak
//I just wanted to use a pointer for sake of consistency with naming(although i
//could have changed the name of the object but) there is no need to use one and
//usually better to avoid them.
//Notes:
//chassis->isSetteled() doesnt work for turns since it doesnt use okapi
//the boolean in set target makes path to be follwed in reverse
//boolean in moveTo() defines if program will wait or not.
//chassis forward or backward movement have their paths removed automatically

void skillsPathThread(void * ignore);

void skills(void) {
  AsyncMotionProfileController *chassis = &chassis::path::profileController;
  chassis::path::make({
      Point{0_ft, 0_ft, 0_deg},
      Point{2_ft, 2.3_ft, 90_deg}
    },
    "Turn1"
  );
  chassis->setTarget("Turn1");
  lift::moveTo(LOW_TOWER, 127, false);
  pros::delay(300);
  intake::moveTo(STACK, 127, false);
  chassis::path::waitUntilSettled("Turn1");
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  chassis->setTarget("Turn2", false);
  chassis::path::waitUntilSettled("Turn2");
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  chassis::forward(48, true);
  return;
}

void skillsPathThread(void * ignore){
  //thread generates paths as robot uses them to avoid memory error
  chassis::path::make({
      Point{0_ft, 0_ft, 0_deg},
      Point{2_ft, -2.3_ft, -90_deg}
    },
    "Turn2"
  );
  chassis::path::make({
      Point{0_ft, 0_ft, 0_deg},
      Point{2_ft, -2.3_ft, -90_deg}
    },
    "Turn2"
  );
  chassis::path::make({
      Point{0_ft, 0_ft, 0_deg},
      Point{2_ft, -2.3_ft, -90_deg}
    },
    "Turn2"
  );
  return;
}
/*

create next path while the current one is running to set setTarget,
be ahead by 2 to 3 paths

*/
