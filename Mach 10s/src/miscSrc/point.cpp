// Author: Jaime Bohorquez
// Knightmare Engineering Club
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

// typedef - for long long int

namespace point
{
     //Variables
     Point start = Point({0_in, 0_in, 0_deg});

     //Data Functions
     Point make(unsigned long long int x, unsigned long long int y, long double theta)
     {    // Use this so the program can make its own paths.
          return okapi::Point
          {
               okapi::literals::operator""_in(x),
               okapi::literals::operator""_in(y),
               okapi::literals::operator""_deg(theta)
          };
     }
}// namespace point
