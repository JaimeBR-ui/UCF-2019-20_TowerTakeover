// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"
#define MIN_POS 0
#define LOW_TOWER 1500
#define HIGH_TOWER 2200
#define ALLIANCE_TOWER 700
#define MAX_POS 3000
#define STACK_HEIGHT 500
#define OFF_GROUND 300

namespace lift{
  //Variables
  extern int wasMoving;

  //Data Functions
  /*
  Gives the caller the current position of the lift.
  @return position: Returns the raw counts of the IME.
  */
  int getPosition(void);
  /*
  Gives the caller a statement regarding the lifts movement.
  @return isStopped: Returns true is the lift is not moving.
  */
  bool isStopped(void);

  //Control Funtions
  /*
  Sets the voltage of the lift motor.
  @param voltage: the voltage to set the lift motor to.
  */
  void setVoltage(int voltage);

  //Autonomous Functions
  /*
  Moves the lift to a designated position on the lift's IME.
  @param position: the unit value to move the lift motor to, in raw counts.
  @param maxSpeed: the maximum allowable speed that the motor will move at.
  @param wait: waits to finish action if true.
  */
  void moveTo(int pos, int maxSpeed, bool wait = false);

  //User Control Functions
  /*
  Assigns the movement of the lift based on the buttons pressed.
  */
  void assign(void);
}
