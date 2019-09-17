// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

using namespace okapi;

namespace chassis{
  namespace path{
    //Variables
//    extern pros::Mutex mutex;
    extern int pathsStored;
    namespace point
    {
      extern Point startingPoint;
    }

    //Data Functions
    bool isSettled(void);

    //Control Functions
    namespace point
    {
      Point make(unsigned long long int x, unsigned long long int y, long double theta);
    }
    ///Path Functions
    void makeAll(std::string autonomousRoutine);

    void moveTo(std::initializer_list<Point>);

    void make(std::initializer_list<Point>, std::string);

    void remove(std::string id);

    void waitUntilSettled();

    void set(std::string id, bool backwards = false);
  }
}
