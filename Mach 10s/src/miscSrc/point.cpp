#include "main.h"

namespace point
{
  //Variables
  Point start = Point({0_in, 0_in, 0_deg});

  //Data Functions
  Point make(unsigned long long int x, unsigned long long int y, long double theta)
  { //use this so the program can make its own paths
    return okapi::Point
    {
      okapi::literals::operator""_in(x),
      okapi::literals::operator""_in(y),
      okapi::literals::operator""_deg(theta)
    };
  }
}// namespace point
