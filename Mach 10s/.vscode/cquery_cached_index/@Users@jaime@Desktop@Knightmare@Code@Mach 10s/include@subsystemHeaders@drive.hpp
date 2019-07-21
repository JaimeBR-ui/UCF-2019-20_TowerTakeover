#include "main.h"
#define SLOWDOWN_FACTOR 2
#define TURN_CONSTANT 0.73
#define POINT_TURN_CONSTANT 0.58

using namespace okapi;

namespace chassis{
  //DATA FUNCTIONS//////////////////////////////////////////////////////////////

  double avgRightSideEncoderUnits(void);

  double avgLeftSideEncoderUnits(void);

  double avgEncoderUnits(void);

  double avgTurningEncoderUnits(void);

  //CONTROL FUNCTIONS///////////////////////////////////////////////////////////
  void setMode(pros::motor_brake_mode_e a);

  void setVoltage(int leftVolt, int rightVolt);

  void setVelocity(int leftVel, int rightVel);

  void GoToTargetTurn(int target, int maxSpeed);

  void tare(void);

  bool isStopped(void);

  void brake(int mills);

  //AUTONOMOUS FUNCTIONS////////////////////////////////////////////////////////
  void turn(int degrees10, int maxSpeed, int accuracyTimer);

  void pointTurn(int degrees10, int maxSpeed, int accuracyTimer);
  //rotates chassis using encoder counts with one side stopped//

  //USER CONTROL FUNCTIONS////////////////////////////////////////////////////
  void assign(void);
}
