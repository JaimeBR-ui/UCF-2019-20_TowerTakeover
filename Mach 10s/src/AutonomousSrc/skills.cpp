#include "main.h"
#define DEPLOY_HEIGHT 400

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

void skills(void) {
  pros::Task deploy = pros::Task(deployClaw);
  chassis::path::make({
      Point{0_ft, 0_ft, 0_deg},
      Point{2_ft, 2.3_ft, 90_deg}
    },
    "Turn1"
  );
  chassis::path::set("Turn1");
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
  /*
  lift::moveTo(DEPLOY_HEIGHT, 127, true);
  intake::moveTo(SCORE, 127, false);
  while(abs(SCORE - intake::getPosition) > 30)
    pros::delay(100);
  lift::moveTo(0, 127, true);
  */
  return;
}

/*
  i think i can make my own isSetteled object
*/
