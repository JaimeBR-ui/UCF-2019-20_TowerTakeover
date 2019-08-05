#include "main.h"

using namespace okapi;
using namespace chassis;

namespace path{
  //Variables
  pros::Mutex mutex;
  int pathsStored = 0;//for reference, must change to use mutex later
  Point startingPoint = Point({0_in, 0_in, 0_deg});
  //motion profiler declarations
  auto RobotChassis = ChassisControllerFactory::create(
    //sets ports and chassis width//
    {1, 10}, // Left motors
    {-2, -9},   // Right motors
    AbstractMotor::gearset::green, // Torque gearset
    {4_in, 15.7_in} // 4 inch wheels, 16 inch wheelbase width
  );
  okapi::AsyncMotionProfileController profileController
    = AsyncControllerFactory::motionProfile(
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
  void make(std::initializer_list<Point> points, std::string id){
    profileController.generatePath(points, id);
    return;
  }
  void remove(std::string id){
    profileController.removePath(id);
    return;
  }
  void waitUntilSettled(void){
    profileController.waitUntilSettled();
    return;
  }
  void set(std::string id, bool backwards){
    profileController.setTarget(id, backwards);
    return;
  }
  void moveTo(std::initializer_list<Point> point){
    profileController.moveTo(point);
    return;
  }
  void skillsPathThread(void * ignore){
    //thread generates paths as robot uses them to avoid stack overflow
    profileController.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{2_ft, -2.3_ft, -90_deg}
      },
      "Turn2"
    );
    pathsStored++;
    while(pathsStored > 2)
      pros::delay(50);
    profileController.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{2_ft, -2.3_ft, -90_deg}
      },
      "Turn2"
    );
    pathsStored++;
    while(pathsStored > 2)
      pros::delay(50);
    profileController.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{2_ft, -2.3_ft, -90_deg}
      },
      "Turn2"
    );
    pathsStored++;
    while(pathsStored > 2)
      pros::delay(50);
    return;
  }
  void makeAll(std::string autonomousRoutine){//creates paths at start of Autonomous//
    if(autonomousRoutine == "skills"){
      profileController.generatePath({
          Point{0_ft, 0_ft, 0_deg},
          Point{2_ft, 2.3_ft, 90_deg}
        },
        "Turn1"
      );
      pathsStored++;
      pros::Task paths(skillsPathThread, &autonomousRoutine);
    }
    return;
  }
}//namespace path
