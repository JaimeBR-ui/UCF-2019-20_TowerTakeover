#include "main.h"

namespace chassis
{
  namespace path
  {
    // Variables
    namespace point
    {
      Point startingPoint = Point({0_in, 0_in, 0_deg});
    }
    // Motion Profiler Declarations
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

    // Data Functions
    bool isSettled(void)
    {
      return profileController.isSettled();
    }

    namespace point
    {
      Point make(unsigned long long int x, unsigned long long int y, long double theta){
        //use this so the program can make its own paths
        return okapi::Point
        {
          okapi::literals::operator""_in(x),
          okapi::literals::operator""_in(y),
          okapi::literals::operator""_deg(theta)
        };
      }
    }// namespace point

    // Path Functions
    void make(std::initializer_list<Point> points, std::string id)
    {
      profileController.generatePath(points, id);
    }

    void remove(std::string id)
    {
      profileController.removePath(id);
    }

    void waitUntilSettled()
    {
      profileController.waitUntilSettled();
    }

    void set(std::string id, bool backwards)
    {
      profileController.setTarget(id, backwards);
    }

    void moveTo(std::initializer_list<Point> point)
    {
      profileController.moveTo(point);
    }
  }// namespace path
}// namespace chassis
