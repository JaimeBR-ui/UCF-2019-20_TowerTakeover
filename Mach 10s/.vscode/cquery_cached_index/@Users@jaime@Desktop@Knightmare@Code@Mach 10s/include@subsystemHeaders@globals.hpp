#include "main.h"

//CONTROLLER DEFINES AND FUNCTIONS
extern pros::Controller controller;
#define LEFT_JOYSTICK pros::E_CONTROLLER_ANALOG_LEFT_Y
#define RIGHT_JOYSTICK pros::E_CONTROLLER_ANALOG_RIGHT_Y
#define OUTTAKE pros::E_CONTROLLER_DIGITAL_L2
#define INTAKE pros::E_CONTROLLER_DIGITAL_L1
#define LIFT_SHIFTER_UP pros::E_CONTROLLER_DIGITAL_R2
#define LIFT_SHIFTER_DOWN pros::E_CONTROLLER_DIGITAL_R1
#define A pros::E_CONTROLLER_DIGITAL_A
#define B pros::E_CONTROLLER_DIGITAL_B
#define X pros::E_CONTROLLER_DIGITAL_X
#define Y pros::E_CONTROLLER_DIGITAL_Y
std::int32_t controllerDigital(pros::controller_digital_e_t channel);
std::int32_t controllerAnalog(pros::controller_analog_e_t channel);
bool anyIntakeButtonPressed();

//MOTORS
extern pros::Motor driveLeftBack;
extern pros::Motor driveLeftFront;
extern pros::Motor driveRightBack;
extern pros::Motor driveRightFront;
extern pros::Motor intakeRight;
extern pros::Motor intakeLeft;
extern pros::Motor liftLeft;
extern pros::Motor liftRight;
void makePaths();
//AUTONS
void skills();
void redFlags();
void blueFlags();
void blueCaps();

//MISCs
#define GYRO_PORT 'H'
