#include "main.h"

//CONTROL FUNCTIONS
namespace intake{
  /*
  Sets the voltage of the intake motor
  @param voltage: the voltage to set the motor to
  */
  void setIntake(int voltage);

  /*
  Changes the value of the intakeMode variable, to be used for loading, firing, intaking, and outtaking
  @param mode: the mode to set the intakeMode to, one of either LOAD, FIRE, INTAKE, OUTTAKE, or STILL
  */
  void setIntakeMode(int mode);

  /*
  Loads an incoming ball until the limit switch under the flywheel is engaged, exiting after 1 second
  */

  //AUTONOMOUS FUNCTIONS

  /*
  The text run in its own separate thread to control the intake while performing other functions. Allows for efficient loading.
  @param ignore: used in order to be run as a thread, do not call this function with any parameter outside of thread creation
  */
  void intakeModeControlFnc(void * ignore);

  //USER CONTROL FUNCTIONS 

  /*
  Checks for action on the left bumpers to designate an intakeMode for the robot, to be sun synchronously with the
  intakeModeControlFnc thread
  */
  void assign();

}
