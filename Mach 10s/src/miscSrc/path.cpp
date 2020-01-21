// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

namespace chassis
{
     namespace path
     {
          // Variables
          auto RobotChassis = ChassisControllerFactory::create(
               // Set ports and chassis width.
               {19, 20}, // Left motors.
               {-11, -12},   // Right motors.
               AbstractMotor::gearset::green, // Torque gearset.
               {4_in, 12_in} // 4 inch wheels, 16 inch wheelbase width.
          );

          auto profileController = AsyncControllerFactory::motionProfile(
               // Set vel, accel, and jerk.
               // Note: Max chassis velocity: 1.064 m/s.
               0.8,  // Maximum linear velocity of the Chassis in m/s  1.0
               1.0,  // Maximum linear acceleration of the Chassis in m/s/s
               10.0, // Maximum linear jerk of the Chassis in m/s/s/s  10.0
               RobotChassis // Robot Chassis Controller
          );

          // Data Functions
          bool is_settled(void)
          {
               return profileController.isSettled();
          }

          // Path Functions
          void make(std::initializer_list<Point> points, std::string id)
          {
               profileController.generatePath(points, id);
          }

          void remove(std::string id)
          {
               profileController.removePath(id);
          }

          void wait_until_settled()
          {
               profileController.waitUntilSettled();
          }

          void set(std::string id, bool backwards)
          {
               profileController.setTarget(id, backwards);
          }

          void move_to(std::initializer_list<Point> point)
          {
               profileController.moveTo(point);
          }
     }// namespace path
}// namespace chassis
