#include "main.h"

//SENSORS
pros::ADIDigitalIn limitSwitch('H');

namespace intake{
  //VARIABLES///////////////////////////////////////////////////////////////////
  bool loadOverride = false;
  enum intakeModes {
    INTAKE_MODE_STACK = 0,
    INTAKE_MODE_RELEASE = 1,
    INTAKE_MODE_SCORE = 2,
    INTAKE_MODE_STORED = 3
  };
  enum intakePositions {
    STACK = 1000,
    RELEASE = 750,
    SCORE = 500
  };
  int intakeMode = INTAKE_MODE_STORED; //Starting position of claw

  //DATA FUNCTIONS//////////////////////////////////////////////////////////////
  double avgEncoderUnits(void){
    return (intakeLeft.get_position() + intakeRight.get_position()) / 2;
  }

  bool isStopped(void){
    return intakeRight.is_stopped()
         && intakeLeft.is_stopped();
  }

  //CONTROL FUNCTIONS///////////////////////////////////////////////////////////
  void setMode(pros::motor_brake_mode_e a){
    intakeRight.set_brake_mode(a);
    intakeLeft.set_brake_mode(a);
    return;
  }

  void setVoltage(int leftVolt, int rightVolt){
    intakeLeft = leftVolt;
    intakeRight = rightVolt;
    return;
  }

  void setVelocity(int leftVel, int rightVel){
    intakeLeft.move_velocity(leftVel);
    intakeRight.move_velocity(rightVel);
    return;
  }

  void tare(void){
    intakeLeft.tare_position();
    intakeRight.tare_position();
    return;
  }

  void intakeStack(void){
    intakeRight.move_absolute(STACK, 127);
    intakeLeft.move_absolute(STACK, 127);
    return;
  }
  void intakeRelease(void){
    intakeRight.move_absolute(RELEASE, 127);
    intakeLeft.move_absolute(RELEASE, 127);
    return;
  }
  void intakeScore(void){
    intakeRight.move_absolute(SCORE, 127);
    intakeLeft.move_absolute(SCORE, 127);
    return;
  }

  //AUTONOMOUS FUNCTIONS////////////////////////////////////////////////////////
  void setIntakeMode(int mode) {
    intakeMode = mode;
    switch(mode) {
      case INTAKE_MODE_STACK:
          intakeStack();
          break;
      case INTAKE_MODE_RELEASE:
          intakeRelease();
          break;
      case INTAKE_MODE_SCORE:
          intakeScore();
          break;
    }
    return;
  }

  //USER CONTROL////////////////////////////////////////////////////////////////
  void assign(void) {
    if(controllerDigital(INTAKE) && intakeMode > 0) {
      intakeMode--;
      setIntakeMode(intakeMode);
      while(controllerDigital(INTAKE)){
        chassis::assign();
        lift::assign();
      }
    }
    else if(controllerDigital(OUTTAKE) && intakeMode < 2) {
      intakeMode++;
      setIntakeMode(intakeMode);
      while(controllerDigital(OUTTAKE)){
        chassis::assign();
        lift::assign();
      }
    }
    return;
  }
}
