// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// Filename: point.hpp

#include "main.h"

typedef unsigned long long int ull_int;

namespace point
{
     // Variables.
     extern Point start;

     //Data functions.
     /*
     Creates a Point struct and returns it.
     @param ull_int x: Unsigned long long int. Distance the robot travels.
                       forward.
     @param ull_int x: Unsigned long long int. Distance the robot travels.
                       sideways.
     @return Point p: Point struct containing the parameters converted into
                      QLength_in and QLength degrees to use in profiler.
     */
     Point make(ull_int x, ull_int y, long double theta);

}// namespace point
