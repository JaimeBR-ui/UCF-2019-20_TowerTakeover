#include "main.h"

namespace chassis
{
  //Variables
  int positionL, positionR;
  std::uint32_t now = pros::millis();
  bool wasMoving = true;

  //Data Functions
  double avgRightSideEncoderUnits(void)
  {
    return (driveRightFront.get_raw_position(&now) +
            driveRightBack.get_raw_position(&now)) / 2;
  }

  double avgLeftSideEncoderUnits(void)
  {
    return (driveLeftFront.get_raw_position(&now) +
            driveLeftBack.get_raw_position(&now)) / 2;
  }

  double avgEncoderUnits(void)
  {
    return (avgRightSideEncoderUnits() + avgLeftSideEncoderUnits()) / 2;
  }

  double avgTurningEncoderUnits(void)
  {
    return (fabs(avgRightSideEncoderUnits()) +
            fabs(avgLeftSideEncoderUnits())) / 2;
  }

  bool isStopped(void)
  {
    return driveRightFront.is_stopped()
         && driveRightBack.is_stopped()
         && driveLeftFront.is_stopped()
         &&  driveLeftBack.is_stopped();
   }

  //Control Functions
  void setMode(pros::motor_brake_mode_e mode)
  {
    driveRightFront.set_brake_mode(mode);
    driveRightBack.set_brake_mode(mode);
    driveLeftFront.set_brake_mode(mode);
    driveLeftBack.set_brake_mode(mode);
  }

  void setVoltage(int leftVolt, int rightVolt)
  { //sets drive to an 8 bit signed voltage int//
    driveRightBack = rightVolt;
    driveRightFront = rightVolt;
    driveLeftBack = leftVolt;
    driveLeftFront = leftVolt;
  }

  void setVelocity(int leftVel, int rightVel)
  { //sets chassis velocity//
    driveRightFront.move_velocity(rightVel);
    driveRightBack.move_velocity(rightVel);
    driveLeftFront.move_velocity(leftVel);
    driveLeftBack.move_velocity(leftVel);
  }

  void turnToTarget(int target, int maxSpeed)
  {
    //chassis goes to encoder target when turning//
    driveLeftBack.move_absolute(target, maxSpeed);
    driveLeftFront.move_absolute(target, maxSpeed);
    driveRightBack.move_absolute(-target, maxSpeed);
    driveRightFront.move_absolute(-target, maxSpeed);
  }

  void tare(void)
  { //sets chassis encoders to zero//
    driveLeftFront.tare_position();
    driveLeftBack.tare_position();
    driveRightFront.tare_position();
    driveRightBack.tare_position();
  }

  void brake(int mills)
  { //brakes drive for set amount of milliseconds//
    setMode(MOTOR_BRAKE_HOLD);
    pros::delay(mills);
    setMode(MOTOR_BRAKE_COAST);
  }

  void moveTo(int targetR, int targetL, int maxSpeed)
  {
    setMode(MOTOR_BRAKE_HOLD);
    driveRightBack.move_absolute(targetR, maxSpeed);
    driveRightFront.move_absolute(targetR, maxSpeed);
    driveLeftBack.move_absolute(targetL, maxSpeed);
    driveLeftFront.move_absolute(targetL, maxSpeed);
  }

  void holdPosition(void)
  {
    positionR = avgRightSideEncoderUnits();
    positionL = avgLeftSideEncoderUnits();
    moveTo(positionR, positionL, 127);
  }

  //Autonomous Functions
  void forward(unsigned long long disp, bool wait)
  {
    path::moveTo({path::startingPoint, path::point::make(disp, 0, 0)});
    if(wait)
      path::waitUntilSettled();
  }
  void back(unsigned long long disp, bool wait)
  {
    path::make({path::startingPoint, path::point::make(disp, 0, 0)}, "temp");
    path::set("temp", true);
    if(wait)
      path::waitUntilSettled();
    path::remove("temp");
  }
  void turn(int degrees10, int maxSpeed, int accuracyTimer)
  {
    //rotates encoder using encoder counts//
    int target = degrees10 * TURN_CONSTANT;
    float myP = 0.18, error = 0.0, ratio;
    int speed = 0;
    int reverse = abs(target) / target;
    int distanceLimitToSpeedUp = target * 0.2 * 900 / degrees10;
    tare();
    while(avgTurningEncoderUnits() < abs(distanceLimitToSpeedUp))
    {
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
      /*printf("encoderloop1: %f; ratio: %f; speed: %d;\n", \
              avgTurningEncoderUnits(), ratio,speed);*/
    }
    while(avgTurningEncoderUnits() > target + 50
          || avgTurningEncoderUnits() < target - 50)
    {
    	error = target - avgTurningEncoderUnits();
    	speed = (myP * error > 127)
        ? 127
        : myP * error;
      speed = (speed >= 20)? speed: 20;
      speed = speed * 1.57;
      setVelocity(speed, -speed);
      /*printf("rotateEncoder(); loop2; avgTurningEncoderUnits(): %f; \
        target: %d; speed: %d;\n", \
        avgTurningEncoderUnits(), target,speed);*/
      pros::delay(20);
    }
    turnToTarget(target, 20);
    pros::delay(accuracyTimer);
    setVoltage(0, 0);
  }

  void pointTurn(int degrees10, int maxSpeed, int accuracyTimer)
  { //rotates chassis using encoder counts with one side stopped//
    int target = degrees10 * POINT_TURN_CONSTANT;
    float myP = 0.18, error = 0.0, ratio;
    int speed = 0;
    int reverse = abs(target) / target;
    int distanceLimitToSpeedUp = target * 0.2 * 900 / degrees10;
    tare();
    if(target > 0)
    {//if we are turning right
      driveRightBack.move_absolute(0, maxSpeed);
      driveRightFront.move_absolute(0, maxSpeed);
      while (avgLeftSideEncoderUnits() < abs(distanceLimitToSpeedUp))
      {
        ratio = (avgLeftSideEncoderUnits() / abs(distanceLimitToSpeedUp) >= 0.15)
          ? avgLeftSideEncoderUnits() / abs(distanceLimitToSpeedUp)
          : 0.15;
        speed = maxSpeed * ratio * reverse * 1.57;
        if (speed>200)
          speed = 200;
        else if (speed< -200)
          speed = -200;
        driveLeftFront.move_velocity(speed);
        driveLeftBack.move_velocity(speed);
        pros::delay(20);
        /*printf("rotateEncoder(); loop2; avgTurningEncoderUnits(): %f; target: \
                %d; speed: %d;\n", avgLeftSideEncoderUnits(), target,speed);*/
        while (avgLeftSideEncoderUnits() > target + 50
              || avgLeftSideEncoderUnits() < target - 50)
        {
          error = target - avgLeftSideEncoderUnits();
          speed = (myP * error > 127)
            ? 127
            : myP * error;
          speed = (speed >= 20)? speed: 20;
          speed = speed * 1.57;
          driveLeftFront.move_velocity(speed);
          driveLeftBack.move_velocity(speed);
          /*printf("rotateEncoder(): avgTurningEncoderUnits(): %f; target: %d; \
                speed: %d;\n", \
          avgLeftSideEncoderUnits(), target,speed);*/
          pros::delay(20);
        }
        driveLeftBack.move_absolute(target, 20);
        driveLeftFront.move_absolute(target, 20);
      }

      }
      else
      {//if we are turning left
        driveLeftBack.move_absolute(0, maxSpeed);
        driveLeftFront.move_absolute(0, maxSpeed);
        while (avgRightSideEncoderUnits() < abs(distanceLimitToSpeedUp))
        {
          ratio = (avgRightSideEncoderUnits() / abs(distanceLimitToSpeedUp) >= 0.15)
            ? avgRightSideEncoderUnits() / abs(distanceLimitToSpeedUp)
            : 0.15;
          speed = maxSpeed * ratio * reverse * 1.57;
          if (speed > 200)
            speed = 200;
          else if (speed < -200)
            speed = -200;
          driveRightFront.move_velocity(speed);
          driveRightBack.move_velocity(speed);
          pros::delay(20);
          /*printf("rotateEncoder(); loop2; avgTurningEncoderUnits(): %f; target: \
                  %d; speed: %d;\n", \
            avgRightSideEncoderUnits(), target,speed);*/
        }
        while (avgRightSideEncoderUnits() > target + 50
              || avgRightSideEncoderUnits() < target - 50)
        {
          error = target - avgRightSideEncoderUnits();
          speed = (myP * error > 127)
            ? 127
            : myP * error;
          speed = (speed >= 20)? speed: 20;
          speed = speed * 1.57;
          driveRightFront.move_velocity(speed);
          driveRightBack.move_velocity(speed);
          /*printf("rotateEncoder(): avgTurningEncoderUnits(): %f; target: \
                  %d; speed: %d;\n", \
                  avgRightSideEncoderUnits(), target,speed);*/
          pros::delay(20);
        }
        driveRightBack.move_absolute(target, 20);
        driveRightFront.move_absolute(target, 20);
      }
      pros::delay(accuracyTimer);
      setVoltage(0, 0);
    }

    //User Control Functions
    void assign(void)
    { //assigns voltage with deadband//
      int l = controllerAnalog(LEFT_JOYSTICK);
      int r = controllerAnalog(RIGHT_JOYSTICK);
      l = (abs(l) > 10) ? l: 0;
      r = (abs(r) > 10) ? r : 0;
      if (lift::getPosition() > 1000)
      {
        l/= SLOWDOWN_FACTOR;
        r/= SLOWDOWN_FACTOR;
      }
      if (l != 0 || r != 0)
      {
        setVoltage(l, r);
        wasMoving = true;
      }
      else
        setVoltage(0, 0);
  }
}//namespace chassis
