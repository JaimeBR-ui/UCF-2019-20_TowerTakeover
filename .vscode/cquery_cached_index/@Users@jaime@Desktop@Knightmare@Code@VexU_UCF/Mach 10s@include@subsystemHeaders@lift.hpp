#include "main.h"

//CONTROL FUNCTIONS
namespace lift{
  /*
  Sets the voltage of the lift motor
  @param voltage: the voltage to set the lift motor to
  */
  void setVoltage(int voltage);

  int getPosition(void);
  //AUTONOMOUS FUNCTIONS

  /*
  Moves the lift to a designated position on the lift motor's integrated encoder
  @param pos: the unit value to move the lift motor to, in raw counts
  @param maxSpeed: the maximum allowable speed that the motor will move at until it reaches the designated position
  @param finish: whether or not to pause all other code until the movement is complete, set to false by default
  */
  void moveTo(int pos, int maxSpeed, bool finish = false);

  //USER CONTROL FUNCTIONS

  /*
  Checks for action on the right bumpers and shifts position either one step up or down
  */
  void assign();
}
