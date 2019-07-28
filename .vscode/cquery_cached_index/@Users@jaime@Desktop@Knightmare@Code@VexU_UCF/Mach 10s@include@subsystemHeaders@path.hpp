#include "main.h"

using namespace okapi;
using namespace chassis;

namespace path{
  //Variables
  extern Point startingPoint;
  ///Path Functions
  void makePaths(void);

  Point makePoint(unsigned long long int x, unsigned long long int y, long double theta);

  void makePath(std::initializer_list<Point>, std::string);

  void waitUntilSettled(void);

  void setPath(std::string s);
}
