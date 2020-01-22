// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// Filename: path.hpp

#include "main.h"

using namespace okapi;

namespace chassis
{
     namespace path
     {
          // Data functions.
          /*
          @return returns if the robot chassis is not moving
          */
          bool is_settled(void);

          // Path functions.
          /*
          Moves robot to desired location absolute from the start.
          @param std::initializer_list<Point>:
               A list of Point structs that contain positions and
               angles at certain points of the path generation.
          */
          void move_to(std::initializer_list<Point>);

          /*
          Generates a path given the waypoints.
          @param std::initializer_list<Point>:
               A list of Point structs that contain positions and
               angles at certain points of the path generation.
          @param std::string:
               ID of the path being generated. Profiler keeps the generated
               paths and to access them you give the ID.
          */
          void make(std::initializer_list<Point>, std::string);

          /*
          Removes path from memory. Used to free up memory.
          @param std::string id:
               ID of the path that needs to be removed.
          */
          void remove(std::string id);

          /*
          Function that waits for the robot reaches its target.
          */
          void wait_until_settled(void);

          /*
          Tells the profiler to go to the specified target.
          @param std::string id:
               ID of the path that will be followed.
          @param bool backwards:
               Boolean that defines if the robot should follow the path
               in reverse.
          */
          void set(std::string id, bool backwards = false);
     }// namespace path
}// namespace chassis
