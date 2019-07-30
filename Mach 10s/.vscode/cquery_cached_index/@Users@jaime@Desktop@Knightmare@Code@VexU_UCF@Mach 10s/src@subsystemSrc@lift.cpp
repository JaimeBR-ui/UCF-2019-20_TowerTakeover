#include "main.h"

using namespace pros;

namespace lift{
  //VARIABLES
  int liftPositionL = liftLeft.get_position(), liftPositionR;
  bool liftWasMoving = true;
  std::uint32_t now = pros::millis();

  enum liftPositions {
    MIN_POS = 0,
    ALLIANCE_TOWER = 700,
    LOW_TOWER = 1500,
    HIGH_TOWER = 2200,
    MAX_POS = 3100
  };
  //DATA FUNCTIONS
  int getPosition(void){
    return liftLeft.get_raw_position(&now);
  }
  //CONTROL FUNCTIONS
  void setVoltage(int voltage) {
    liftLeft = voltage;
    liftRight = voltage;
    liftWasMoving = true;
    return;
  }

  void setMode(pros::motor_brake_mode_e mode){
    liftLeft.set_brake_mode(mode);
    liftRight.set_brake_mode(mode);
    return;
  }

  //AUTONOMOUS FUNCTIONS
  void moveTo(int target, int maxSpeed, bool wait) {
    liftLeft.move_absolute(target, maxSpeed);
    liftRight.move_absolute(target, maxSpeed);
    liftWasMoving = true;
    if(wait) {
      while(fabs(target - getPosition()) > 10){
        chassis::assign();
      }
    }
    return;
  }

  void holdPosition(void){
    setVoltage(0);
    setMode(MOTOR_BRAKE_HOLD);
    liftPositionL = (liftLeft.get_raw_position(&now) > 0)
      ? liftLeft.get_raw_position(&now)
      : 0;
    liftPositionR = (liftRight.get_raw_position(&now) > 0)
      ? liftRight.get_raw_position(&now)
      : 0;
    liftLeft.move_absolute(liftPositionL, 127);
    liftRight.move_absolute(liftPositionR, 127);
    liftWasMoving = false;
    return;
  }

  //USER CONTROL FUNCTIONS

  void assign(void){
    printf("liftval: %d\n", getPosition());

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
    }
    else if(controllerDigital(LIFT_SHIFTER_DOWN)){
          setMode(MOTOR_BRAKE_COAST);
          setVoltage(127);
    }
    else if(liftWasMoving){
        holdPosition();
    }
    return;
  }
}
