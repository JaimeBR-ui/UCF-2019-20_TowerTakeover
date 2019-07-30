#include "main.h"

using namespace okapi;
using namespace chassis;

namespace path{
  //Variables
  extern Point startingPoint;
  //Data Functions
  bool isSettled(void);
  //Control Functions
  Point makePoint(unsigned long long int x, unsigned long long int y, long double theta);
  ///Path Functions
  void makePaths(void);

  void moveTo(std::initializer_list<Point>);

  void makePath(std::initializer_list<Point>, std::string);

  void removePath(std::string id);

  void waitUntilSettled(void);

  void setPath(std::string id);

  void setPath(std::string id, bool backwards);
}
