#include "main.h"

namespace lift{
  //Variables
  int liftPositionL = liftLeft.get_position(), liftPositionR;
  int liftWasMoving = 1;
  std::uint32_t now = pros::millis();

  //Data Functions
  int getPosition(void){
    return (liftLeft.get_raw_position(&now) +
            liftLeft.get_raw_position(&now)) / 2;
  }

  bool isStopped(void){
    return liftLeft.is_stopped()
       && liftRight.is_stopped();
  }

  //Control Functions
  void setVoltage(int voltage) {
    liftLeft = voltage;
    liftRight = voltage;
    return;
  }

  void setMode(pros::motor_brake_mode_e mode){
    liftLeft.set_brake_mode(mode);
    liftRight.set_brake_mode(mode);
    return;
  }

  //Autonomous Functions
  void holdPosition(void){
    setVoltage(0);
    setMode(MOTOR_BRAKE_HOLD);
    liftPositionL = (liftLeft.get_raw_position(&now) > 0)
      ? liftLeft.get_raw_position(&now)
      : 0;
    liftPositionR = (liftRight.get_raw_position(&now) > 0)
      ? liftRight.get_raw_position(&now)
      : 0;
    if(liftWasMoving == 1){
      liftLeft.move_absolute(liftPositionL, 127);
      liftRight.move_absolute(liftPositionR, 127);
      liftWasMoving = 0;
      return;
    }
    /*//why do this when I can just lower the speed lol
    setMode(MOTOR_BRAKE_COAST);
    for(int i = 0; i < 64; i++){//slows down to prevent possible gear skip
      setVoltage(i);
      pros::delay(50);
    }
    setMode(MOTOR_BRAKE_HOLD);
    */
    int maxSpeed = 60;
    liftLeft.move_absolute(liftPositionL, maxSpeed);
    liftRight.move_absolute(liftPositionR, maxSpeed);
    liftWasMoving = 0;
    return;
  }

  void moveTo(int position, int maxSpeed, bool wait) {
    liftLeft.move_absolute(position, maxSpeed);
    liftRight.move_absolute(position, maxSpeed);
    if(position - getPosition() > 0)
      liftWasMoving = 1;
    else
      liftWasMoving = -1;
    if(wait && pros::competition::is_autonomous())
      while(fabs(position - getPosition()) > 10)
        pros::delay(20);
    else if(wait)
      while(fabs(position - getPosition()) > 10)
        chassis::assign();
    holdPosition();
    return;
  }

  //User Control Functions
  void assign(void){
    std::cout << "liftval: " << getPosition() << std::endl;
    if(controllerDigital(A))
      moveTo(MAX_POS, 127, true);
    else if(controllerDigital(B))
      moveTo(ALLIANCE_TOWER, 127, true);
    else if(controllerDigital(X))
      moveTo(HIGH_TOWER, 127, true);
    else if(controllerDigital(Y))
      moveTo(LOW_TOWER, 127, true);
    else if(controllerDigital(LIFT_SHIFTER_UP)){
          setMode(MOTOR_BRAKE_COAST);
          if(getPosition() < 0)
            setVoltage(-15);
          else if(getPosition() < 107)
            setVoltage(-(getPosition()+20));
          else
            setVoltage(-127);
          liftWasMoving = -1;
    }
    else if(controllerDigital(LIFT_SHIFTER_DOWN)){
          setMode(MOTOR_BRAKE_COAST);
          if(getPosition() > 3100)
            setVoltage(0);
          else
            setVoltage(127);
          liftWasMoving = 1;
    }
    else if(liftWasMoving != 0)
        holdPosition();
    return;
  }
}//namespace lift
