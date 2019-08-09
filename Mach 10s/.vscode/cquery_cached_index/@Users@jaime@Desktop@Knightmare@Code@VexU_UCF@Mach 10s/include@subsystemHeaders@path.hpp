#include "main.h"

using namespace okapi;

namespace chassis{
  namespace path{
    //Variables
    extern pros::Mutex mutex;
    extern int pathsStored;
    extern Point startingPoint;
    extern AsyncMotionProfileController profileController;

    //Data Functions
    bool isSettled(void);

    //Control Functions
    namespace point{
      Point make(unsigned long long int x, unsigned long long int y, long double theta);
    }
    ///Path Functions
    void makeAll(std::string autonomousRoutine);

    void moveTo(std::initializer_list<Point>);

    void make(std::initializer_list<Point>, std::string);

    void remove(std::string id);

    void waitUntilSettled(std::string id = "");

    void set(std::string id, bool backwards = false);
  }
}
