#include "main.h"
#define STACK 1000
#define RELEASE 750
#define SCORE 500

namespace intake{
  //Data Functions
  /*
  returns data regarding the intake's location.
  @return position: return average location of the intake.
  */
  int getPosition(void);
  /*
  gives feedback regarding the movement of the intake.
  @return isStopped: return true if intake is stopped, else otherwise.
  */
  bool isStopped(void);

  //Control Functions
  /*
  Sets the voltage of the intake motor
  @param voltage: the voltage to set the motor to
  */
  void setVoltage(int leftVolt, int rightVolt);

  //Autonomous Functions
  /*
  Sends the intake to the position specified
  @param posiition: Sends intake to specified position can use predefined conditions
                    such as STACK, RELEASE, or SCORE.
  @param maxSpeed: Specifies the meximum speed when going to target.
  @param wait: Defines the behavior of the function to act like a thread or function
  */
  void moveTo(int position, int maxSpeed, bool wait);

  //User Control Functions
  /*
  Checks for action on the left bumpers to designate an intakeMode for the robot
  */
  void assign(void);

}//namespace intake
