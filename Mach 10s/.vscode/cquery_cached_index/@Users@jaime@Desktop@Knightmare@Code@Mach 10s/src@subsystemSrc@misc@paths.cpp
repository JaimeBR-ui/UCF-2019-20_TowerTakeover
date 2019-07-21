#include "main.h"

using namespace okapi;
using namespace chassis;

namespace path{
  void makePaths(void){//creates paths at start of Autonomous//
    makePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{2_ft, 2.3_ft, 90_deg}
      },
      "Turn1"
    );
    makePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{2_ft, -2.3_ft, -90_deg}
      },
      "Turn2"
    );
    makePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{4.2_ft, 0_ft, 0_deg}
      },
      "Straight4"
    );
    return;
  }
}
