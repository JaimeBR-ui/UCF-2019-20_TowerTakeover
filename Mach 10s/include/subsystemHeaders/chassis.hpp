// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"
#define SLOWDOWN_FACTOR 2
#define TURN_CONSTANT 0.75
#define POINT_TURN_CONSTANT 1.5

namespace chassis{
  //Variables
  extern int positionL, positionR;
  extern std::uint32_t now;
  extern bool wasMoving;
  //DATA FUNCTIONS//////////////////////////////////////////////////////////////
  double avgRightSideEncoderUnits(void);

  double avgLeftSideEncoderUnits(void);

  double avgEncoderUnits(void);

  double avgTurningEncoderUnits(void);

  //CONTROL FUNCTIONS///////////////////////////////////////////////////////////
  void setMode(pros::motor_brake_mode_e);

  void setVoltage(int leftVolt, int rightVolt);

  void setVelocity(int leftVel, int rightVel);

  void turnToTarget(int target, int maxSpeed);

  void tare(void);

  bool isStopped(void);

  void brake(int mills);

  //AUTONOMOUS FUNCTIONS////////////////////////////////////////////////////////
  void forward(unsigned long long int disp, bool wait);

  void back(unsigned long long int disp, bool wait);

  void turn(int degrees10, int maxSpeed, int accuracyTimer);

  void pointTurn(int degrees10, int maxSpeed, int accuracyTimer);
  //rotates chassis using encoder counts with one side stopped//

  //USER CONTROL FUNCTIONS////////////////////////////////////////////////////
  void assign(void);
}
