#include "main.h"

namespace chassis{
  //VARIABLES///////////////////////////////////////////////////////////////////
  int positionL, positionR;
  std::uint32_t now = pros::millis();
  bool wasMoving = true;

  //DATA FUNCTIONS//////////////////////////////////////////////////////////////

  double avgRightSideEncoderUnits(void){
    return (driveRightFront.get_raw_position(&now)+ driveRightBack.get_raw_position(&now)) / 2;
  }

  double avgLeftSideEncoderUnits(void){
    return (driveLeftFront.get_raw_position(&now) + driveLeftBack.get_raw_position(&now)) / 2;
  }

  double avgEncoderUnits(void) {
    return (avgRightSideEncoderUnits() + avgLeftSideEncoderUnits()) / 2;
  }

  double avgTurningEncoderUnits(void){
    return (fabs(avgRightSideEncoderUnits()) + fabs(avgLeftSideEncoderUnits())) / 2;
  }

  bool isStopped(void){
    return driveRightFront.is_stopped()
         && driveRightBack.is_stopped()
         && driveLeftFront.is_stopped()
         &&  driveLeftBack.is_stopped();
   }

  //CONTROL FUNCTIONS///////////////////////////////////////////////////////////

  void setMode(pros::motor_brake_mode_e a){
    driveRightFront.set_brake_mode(a);
    driveRightBack.set_brake_mode(a);
    driveLeftFront.set_brake_mode(a);
    driveLeftBack.set_brake_mode(a);
    return;
  }

  void setVoltage(int leftVolt, int rightVolt) { //sets drive to an 8 bit signed voltage int//
    driveRightBack = rightVolt;
    driveRightFront = rightVolt;
    driveLeftBack = leftVolt;
    driveLeftFront = leftVolt;
    return;
  }

  void setVelocity(int leftVel, int rightVel){ //sets chassis velocity//
    driveRightFront.move_velocity(rightVel);
    driveRightBack.move_velocity(rightVel);
    driveLeftFront.move_velocity(leftVel);
    driveLeftBack.move_velocity(leftVel);
    return;
  }

  void GoToTargetTurn(int target, int maxSpeed){
    //chassis goes to encoder target when turning//
    driveLeftBack.move_absolute(target, maxSpeed);
    driveLeftFront.move_absolute(target, maxSpeed);
    driveRightBack.move_absolute(-target, maxSpeed);
    driveRightFront.move_absolute(-target, maxSpeed);
    return;
  }

  void tare(void) { //sets chassis encoders to zero//
    driveLeftFront.tare_position();
    driveLeftBack.tare_position();
    driveRightFront.tare_position();
    driveRightBack.tare_position();
    return;
  }

  void brake(int mills){ //brakes drive for set amount of milliseconds//
    driveLeftFront.set_brake_mode(MOTOR_BRAKE_HOLD);
    driveLeftBack.set_brake_mode(MOTOR_BRAKE_HOLD);
    driveRightFront.set_brake_mode(MOTOR_BRAKE_HOLD);
    driveRightBack.set_brake_mode(MOTOR_BRAKE_HOLD);
    pros::delay(mills);
    driveLeftFront.set_brake_mode(MOTOR_BRAKE_COAST);
    driveLeftBack.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRightFront.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRightBack.set_brake_mode(MOTOR_BRAKE_COAST);
    return;
  }

  void moveTo(int targetR, int targetL, int maxSpeed) {
    setMode(MOTOR_BRAKE_HOLD);
    driveRightBack.move_absolute(targetR, maxSpeed);
    driveRightFront.move_absolute(targetR, maxSpeed);
    driveLeftBack.move_absolute(targetL, maxSpeed);
    driveLeftFront.move_absolute(targetL, maxSpeed);
    return;
  }

  void holdPosition(void){
    positionR = avgRightSideEncoderUnits();
    positionL = avgLeftSideEncoderUnits();
    moveTo(positionR, positionL, 127);
    return;
  }

  //AUTONOMOUS FUNCTIONS////////////////////////////////////////////////////////
  void turn(int degrees10, int maxSpeed, int accuracyTimer)
    { //rotates encoder using encoder counts//
    int target = degrees10 * TURN_CONSTANT;
    float myP = 0.18, error = 0.0, ratio;
    int speed = 0;
    int reverse = abs(target) / target;
    int distanceLimitToSpeedUp = target * 0.2 * 900 / degrees10;
    tare();
    while(avgTurningEncoderUnits() < abs(distanceLimitToSpeedUp)){
      ratio = (avgTurningEncoderUnits() / abs(distanceLimitToSpeedUp) >= 0.15)
        ? avgTurningEncoderUnits() / abs(distanceLimitToSpeedUp)
        : 0.15;
      speed = maxSpeed * ratio * reverse * 1.57;
      if(speed>200)
        speed = 200;
      else if (speed< -200)
        speed = -200;
      setVelocity(speed, -speed);
      pros::delay(20);
      printf("encoderloop1: %f; ratio: %f; speed: %d;\n", \
              avgTurningEncoderUnits(), ratio,speed);
    }
    while(avgTurningEncoderUnits() > target + 50
          || avgTurningEncoderUnits() < target - 50) {
    	error = target - avgTurningEncoderUnits();
    	speed = (myP * error > 127)
        ? 127
        : myP * error;
      speed = (speed >= 20)? speed: 20;
      speed = speed * 1.57;
      setVelocity(speed, -speed);
      printf("rotateEncoder(); loop2; avgTurningEncoderUnits(): %f; \
        target: %d; speed: %d;\n", \
        avgTurningEncoderUnits(), target,speed);
      pros::delay(20);
    }
    GoToTargetTurn(target, 20);
    pros::delay(accuracyTimer);
    setVoltage(0, 0);
    return;
}

  void pointTurn(int degrees10, int maxSpeed, int accuracyTimer){
    //rotates chassis using encoder counts with one side stopped//
    int target = degrees10 * POINT_TURN_CONSTANT;
    float myP = 0.18, error = 0.0, ratio;
    int speed = 0;
    int reverse = abs(target) / target;
    int distanceLimitToSpeedUp = target * 0.2 * 900 / degrees10;
    tare();
    if(target > 0){//if we are turning right
      driveRightBack.move_absolute(0, maxSpeed);
      driveRightFront.move_absolute(0, maxSpeed);
      while(avgLeftSideEncoderUnits() < abs(distanceLimitToSpeedUp)){
        ratio = (avgLeftSideEncoderUnits() / abs(distanceLimitToSpeedUp) >= 0.15)
          ? avgLeftSideEncoderUnits() / abs(distanceLimitToSpeedUp)
          : 0.15;
        speed = maxSpeed * ratio * reverse * 1.57;
        if(speed>200)
          speed = 200;
        else if (speed< -200)
          speed = -200;
        driveLeftFront.move_velocity(speed);
        driveLeftBack.move_velocity(speed);
        pros::delay(20);
        printf("rotateEncoder(); loop2; avgTurningEncoderUnits(): %f; target: \
                %d; speed: %d;\n", \
          avgLeftSideEncoderUnits(), target,speed);
        while(avgLeftSideEncoderUnits() > target + 50
              || avgLeftSideEncoderUnits() < target - 50) {
          error = target - avgLeftSideEncoderUnits();
          speed = (myP * error > 127)
            ? 127
            : myP * error;
          speed = (speed >= 20)? speed: 20;
          speed = speed * 1.57;
          driveLeftFront.move_velocity(speed);
          driveLeftBack.move_velocity(speed);
          printf("rotateEncoder(): avgTurningEncoderUnits(): %f; target: %d; \
                speed: %d;\n", \
          avgLeftSideEncoderUnits(), target,speed);
          pros::delay(20);
        }
        driveLeftBack.move_absolute(target, 20);
        driveLeftFront.move_absolute(target, 20);
      }

      }else{//if we are turning left
        driveLeftBack.move_absolute(0, maxSpeed);
        driveLeftFront.move_absolute(0, maxSpeed);
        while(avgRightSideEncoderUnits() < abs(distanceLimitToSpeedUp)){
          ratio = (avgRightSideEncoderUnits() / abs(distanceLimitToSpeedUp) >= 0.15)
            ? avgRightSideEncoderUnits() / abs(distanceLimitToSpeedUp)
            : 0.15;
          speed = maxSpeed * ratio * reverse * 1.57;
          if(speed > 200)
            speed = 200;
          else if (speed < -200)
            speed = -200;
          driveRightFront.move_velocity(speed);
          driveRightBack.move_velocity(speed);
          pros::delay(20);
          printf("rotateEncoder(); loop2; avgTurningEncoderUnits(): %f; target: \
                  %d; speed: %d;\n", \
            avgRightSideEncoderUnits(), target,speed);
        }
        while(avgRightSideEncoderUnits() > target + 50
              || avgRightSideEncoderUnits() < target - 50) {
          error = target - avgRightSideEncoderUnits();
          speed = (myP * error > 127)
            ? 127
            : myP * error;
          speed = (speed >= 20)? speed: 20;
          speed = speed * 1.57;
          driveRightFront.move_velocity(speed);
          driveRightBack.move_velocity(speed);
          printf("rotateEncoder(): avgTurningEncoderUnits(): %f; target: \
                  %d; speed: %d;\n", \
                  avgRightSideEncoderUnits(), target,speed);
          pros::delay(20);
        }
        driveRightBack.move_absolute(target, 20);
        driveRightFront.move_absolute(target, 20);
      }
      pros::delay(accuracyTimer);
      setVoltage(0, 0);
      return;
    }

    //USER CONTROL FUNCTIONS////////////////////////////////////////////////////
    void assign(void) { //assigns voltage with deadband//
      int l = controllerAnalog(LEFT_JOYSTICK);
      int r = controllerAnalog(RIGHT_JOYSTICK);
      l = (abs(l) > 10) ? l: 0;
      r = abs(r) > 10 ? r : 0;
      if(lift::getPosition() > 200){
        l/= SLOWDOWN_FACTOR;
        r/= SLOWDOWN_FACTOR;
      }
      if(l != 0 || r != 0){
        setMode(MOTOR_BRAKE_COAST);
        setVoltage(l, r);
        wasMoving = true;
      }
      else if(isStopped() && wasMoving){
        wasMoving = false;
        holdPosition();
      }
      return;
  }
}
