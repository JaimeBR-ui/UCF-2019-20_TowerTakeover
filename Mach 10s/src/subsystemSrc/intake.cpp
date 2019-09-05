#include "main.h"

namespace intake
{
  // Variables
  enum intakeModes
  {
    INTAKE_MODE_STACK = 0,
    INTAKE_MODE_RELEASE = 1,
    INTAKE_MODE_SCORE = 2,
    INTAKE_MODE_STORED = 3
  };

  bool wasMoving = true;
  int intakeMode = INTAKE_MODE_STORED; // Starting position of intake
  std::uint32_t now = pros::millis();

  // Data Functions
  int getPosition(void)
  {
    return (intakeLeft.get_position() + intakeRight.get_position()) / 2;
  }

  bool isStopped(void)
  {
    return intakeRight.is_stopped()
         && intakeLeft.is_stopped();
  }

  bool changedToPressed(std::int32_t a)
  {
    static int lastVal = 0;
    static int newVal = 0;
    lastVal = newVal;
    if(a == 0)
      newVal = 0;
    else
      newVal = 1;
    return newVal == 1 && lastVal == 0;
  }

  // Control Functions
  void setMode(pros::motor_brake_mode_e mode)
  {
    intakeRight.set_brake_mode(mode);
    intakeLeft.set_brake_mode(mode);
  }

  void setVoltage(int voltage)
  {
    intakeLeft = voltage;
    intakeRight = voltage;
  }

  void setVelocity(int leftVel, int rightVel)
  {
    intakeLeft.move_velocity(leftVel);
    intakeRight.move_velocity(rightVel);
  }

  void tare(void)
  {
    intakeLeft.tare_position();
    intakeRight.tare_position();
  }

  // Autonomous Functions
  void moveTo(int position, int maxSpeed, bool wait)
  {
    setMode(MOTOR_BRAKE_HOLD);
    intakeLeft.move_absolute(position, maxSpeed);
    intakeRight.move_absolute(position, maxSpeed);
    if (wait && pros::competition::is_autonomous())
      while (fabs(position - getPosition()) > 200)
        pros::delay(20);

    else if (wait)
      while (fabs(position - getPosition()) > 10)
      {
        chassis::assign();
        lift::assign();
      }
  }

  void holdPosition(void)
  {
    int maxSpeed = 127, positionL, positionR;
    setVoltage(0);
    setMode(MOTOR_BRAKE_HOLD);
    positionL = intakeLeft.get_raw_position(&now);
    positionR = intakeRight.get_raw_position(&now);
    intakeLeft.move_absolute(positionL, maxSpeed);
    intakeRight.move_absolute(positionR, maxSpeed);
    wasMoving = false;
  }

  // User Control Functions
  void setIntakeMode(int mode)
  {
    switch (mode)
    {
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
  }

  void assign(void)
  {
    if (controllerDigital(INTAKE))
    {
          setMode(MOTOR_BRAKE_COAST);
          setVoltage(-21);
          wasMoving = true;
    }
    else if (controllerDigital(OUTTAKE))
    {
          setMode(MOTOR_BRAKE_COAST);
          setVoltage(21);
          wasMoving = true;
    }
    else if (wasMoving)
        holdPosition();
    //printf("%10d", getPosition());
  }
}// namespace intake


/*
// past toggle code
if (controllerDigital(INTAKE) && intakeMode > 0)
{
  intakeMode--;
  setIntakeMode(intakeMode);
  while (controllerDigital(INTAKE))
  {
    chassis::assign();
    lift::assign();
  }
}
else if (controllerDigital(OUTTAKE) && intakeMode < 4)
{
  intakeMode++;
  setIntakeMode(intakeMode);
  while (controllerDigital(OUTTAKE))
  {
    chassis::assign();
    lift::assign();
  }
}
*/
