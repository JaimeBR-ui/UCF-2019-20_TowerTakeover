#include "main.h"

using namespace okapi;
using namespace chassis;

namespace path{
  //Variables
  Point startingPoint = Point({0_in, 0_in, 0_deg});
  //motion profiler declarations
  auto RobotChassis = ChassisControllerFactory::create(
    //sets ports and chassis width//
    {1, 10}, // Left motors
    {-2, -9},   // Right motors
    AbstractMotor::gearset::green, // Torque gearset
    {4_in, 15.7_in} // 4 inch wheels, 16 inch wheelbase width
  );
  auto profileController = AsyncControllerFactory::motionProfile(
    // sets vel, accel, and jerk
    //max chassis velocity: 1.064 m/s
    1.0,  // Maximum linear velocity of the Chassis in m/s  1.0
    2.0,  // Maximum linear acceleration of the Chassis in m/s/s  2.0
    10.0, // Maximum linear jerk of the Chassis in m/s/s/s  10.0
    RobotChassis // Robot Chassis Controller
  );
  //Data Functions
  bool isSettled(void){
    return profileController.isSettled();
  }
  //Control Functions
  Point makePoint(unsigned long long int x, unsigned long long int y, long double theta){
    //use this so the program can make its own paths
    return okapi::Point{
      okapi::literals::operator""_in(x),
      okapi::literals::operator""_in(y),
      okapi::literals::operator""_deg(theta)
    };
  }
  ///Path functions
  void makePath(std::initializer_list<Point> points, std::string id){
    profileController.generatePath(points, id);
    return;
  }
  void removePath(std::string id){
    profileController.removePath(id);
  }
  void waitUntilSettled(void){
    profileController.waitUntilSettled();
    return;
  }
  void setPath(std::string id, bool backwards){
    profileController.setTarget(id, backwards);
    return;
  }
  void setPath(std::string id){
    profileController.setTarget(id);
    return;
  }
  void moveTo(std::initializer_list<Point> point){
    profileController.moveTo(point);
    return;
  }
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
}
