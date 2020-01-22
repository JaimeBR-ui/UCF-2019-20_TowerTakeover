// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// Filename: point.cpp

#include "main.h"

namespace point
{
     // Variables.
     Point start = Point({0_in, 0_in, 0_deg});

     // Data functions.
     Point make(ull_int x, ull_int y, long double theta)
     {
          // Use this so the program can make its own paths.
          return okapi::Point
          {
               okapi::literals::operator""_in(x),
               okapi::literals::operator""_in(y),
               okapi::literals::operator""_deg(theta)
          };
     }

}// namespace point
