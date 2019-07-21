#include "main.h"

using namespace okapi;

//MOTORS////////////////////////////////////////////////////////////////////////////////////

//Drive
pros::Motor driveLeftFront(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
//Lift
pros::Motor liftRight(3, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor liftLeft(8, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
//Intake
pros::Motor intakeRight(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeLeft(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

//CONTROLLER DEFINES AND FUNCTIONS
pros::Controller controller(pros::E_CONTROLLER_MASTER);

std::int32_t controllerDigital(pros::controller_digital_e_t channel) {
  return controller.get_digital(channel);
}

std::int32_t controllerAnalog(pros::controller_analog_e_t channel) {
  return controller.get_analog(channel);
}
//AUTONOMOS ROUTINES/////////////////////////////////////////////////////////////////////////////////////

void skills(void) {
  path::makePaths();
  path::setPath("Turn1");
  path::waitUntilSettled();
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  path::setPath("Turn2");
  path::waitUntilSettled();
  pros::delay(500);
  chassis::turn(900, 127, 400);
  pros::delay(500);
  path::setPath("Straight4");
  path::waitUntilSettled();
  return;
}

void redFlags(void) {
  for (int i = 0; i<4; i++){
    std::cout << "Loop: " << i+1 << "\n";
    chassis::turn(900, 127, 400);
  }
  return;
}

void blueFlags(void) {
  path::makePaths();
  path::setPath("Turn1");
  path::waitUntilSettled();
  return;
}

void blueCaps(void) {
  return;
}
