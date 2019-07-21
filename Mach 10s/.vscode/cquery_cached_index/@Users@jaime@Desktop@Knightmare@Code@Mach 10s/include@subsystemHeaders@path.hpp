#include "main.h"

using namespace okapi;
using namespace chassis;

namespace path{
  ///Path functions
  void makePaths(void);

  Point makePoint();

  void makePath(std::initializer_list<Point> p, std::string s);

  void waitUntilSettled(void);

  void setPath(std::string s);
}
