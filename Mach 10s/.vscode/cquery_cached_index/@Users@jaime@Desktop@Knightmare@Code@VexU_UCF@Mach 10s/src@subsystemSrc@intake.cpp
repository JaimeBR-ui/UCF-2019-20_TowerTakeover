#include "main.h"

namespace intake{
  //Variables
  enum intakeModes {
    INTAKE_MODE_STACK = 0,
    INTAKE_MODE_RELEASE = 1,
    INTAKE_MODE_SCORE = 2,
    INTAKE_MODE_STORED = 3
  };
  int intakeMode = INTAKE_MODE_STORED; //Starting position of intake

  //Data Functions
  int getPosition(void){
    return (intakeLeft.get_position() + intakeRight.get_position()) / 2;
  }

  bool isStopped(void){
    return intakeRight.is_stopped()
         && intakeLeft.is_stopped();
  }

  bool changedToPressed(std::int32_t a){
    static int lastVal = 0;
    static int newVal = 0;
    lastVal = newVal;
    if(a == 0)
      newVal = 0;
    else
      newVal = 1;
    return newVal == 1 && lastVal == 0;
  }

  //Control Functions
  void setMode(pros::motor_brake_mode_e mode){
    intakeRight.set_brake_mode(mode);
    intakeLeft.set_brake_mode(mode);
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

  //Autonomous Functions
  void moveTo(int position, int maxSpeed, bool wait) {
    intakeLeft.move_absolute(position, maxSpeed);
    intakeRight.move_absolute(position, maxSpeed);
    if(wait && pros::competition::is_autonomous())
      while(fabs(position - getPosition()) > 10)
        pros::delay(20);
    else if(wait)
      while(fabs(position - getPosition()) > 10){
        chassis::assign();
        lift::assign();
      }
    return;
  }

  //User Control Functions
  void setIntakeMode(int mode) {
    switch(mode) {
      case INTAKE_MODE_STACK:
          moveTo(STACK, 127, false);
          break;
      case INTAKE_MODE_RELEASE:
          moveTo(RELEASE, 127, false);
          break;
      case INTAKE_MODE_SCORE:
          moveTo(SCORE, 127, false);
          break;
    }
    return;
  }

  void assign(void) {
    if(controllerDigital(INTAKE) && intakeMode > 0) {
      intakeMode--;
      setIntakeMode(intakeMode);
      while(controllerDigital(INTAKE)){
        chassis::assign();
        lift::assign();
      }
    }
    else if(controllerDigital(OUTTAKE) && intakeMode < 4) {
      intakeMode++;
      setIntakeMode(intakeMode);
      while(controllerDigital(OUTTAKE)){
        chassis::assign();
        lift::assign();
      }
    }
    std::cout << "intake " << getPosition() << std::endl;
    return;
  }
}//namespace intake
