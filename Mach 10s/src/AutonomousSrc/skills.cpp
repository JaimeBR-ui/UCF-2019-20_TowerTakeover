#include "main.h"

/*
set targets in lift.hpp
  MIN_POS LOW_TOWER  HIGH_TOWER ALLIANCE_TOWER MAX_POS
set targets in intake.hpp
  STACK RELEASE SCORE
*/

//Notes:
//chassis->isSetteled() doesnt work for turns since it doesnt use okapi
//the boolean in set target makes path to be follwed in reverse
//boolean in moveTo() defines if program will wait or not.
//chassis forward or backward movement have their paths removed automatically

void deployClaw(void * ignore);

void skills(void) {
  pros::Task deploy = pros::Task(deployClaw);
  chassis::path::make({
      Point{0_ft, 0_ft, 0_deg},
      Point{2_ft, 2.3_ft, 90_deg}
    },
    "Turn1"
  );
  chassis::path::set("Turn1");
  lift::moveTo(LOW_TOWER, 127, false);
  pros::delay(300);
  intake::moveTo(STACK, 127, false);
  chassis::path::make({
      Point{0_ft, 0_ft, 0_deg},
      Point{2_ft, -2.3_ft, -90_deg}
    },
    "Turn2"
  );
  chassis::path::waitUntilSettled("Turn1");
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  chassis::path::set("Turn2", false);
  chassis::path::waitUntilSettled("Turn2");
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  chassis::forward(48, true);
  return;
}

void deployClaw(void * ignore){
  //thread that deploys the robot's claw
  return;
}

/*

create next path while the current one is running to set setTarget,
be ahead by 2 to 3 paths

*/
