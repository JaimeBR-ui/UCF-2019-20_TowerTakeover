#include "main.h"

using namespace okapi;
using namespace chassis;

//motion profiler declarations
auto RobotChassis = ChassisControllerFactory::create(
  //sets ports and chassis width//
  {1, 10}, // Left motors
  {-2, -9},   // Right motors
  AbstractMotor::gearset::green, // Torque gearset
  {4_in, 15.7_in} // 4 inch wheels, 16 inch wheelbase width
);

auto profileController = AsyncControllerFactory::motionProfile(
  // sets vel, accel, and jerk//
  //max chassis velocity: 1.064 m/s
  1.0,  // Maximum linear velocity of the Chassis in m/s  1.0
  2.0,  // Maximum linear acceleration of the Chassis in m/s/s  2.0
  10.0, // Maximum linear jerk of the Chassis in m/s/s/s  10.0
  RobotChassis // Robot Chassis Controller
);

namespace path{

  Point makePoint(unsigned long long int x, unsigned long long int y, unsigned long long int theta){//use this so the program can make its own paths
    QLength x_in = literals::operator""_in(x);
    QLength y_in = okapi::literals::operator""_in(y);
    QAngle theta_deg = okapi::literals::operator""_deg(theta);
    Point p = Point();
    p.x = x_in;
    p.y = y_in;
    p.theta = theta_deg;
    return p;
  }
  ///Path functions
  void makePaths(void){//creates paths at start of Autonomous//
    profileController.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{2_ft, 2.3_ft, 90_deg}
      },
      "Turn1"
    );
    profileController.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{2_ft, -2.3_ft, -90_deg}
      },
      "Turn2"
    );
    profileController.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{4.2_ft, 0_ft, 0_deg}
      },
      "Straight4"
    );
    return;
  }
  void makePath(std::initializer_list<Point> p, std::string s){
    profileController.generatePath(p, s);
    return;
  }
  void waitUntilSettled(void){
    profileController.waitUntilSettled();
    return;
  }
  void setPath(std::string s){
    profileController.setTarget();
  }
}
