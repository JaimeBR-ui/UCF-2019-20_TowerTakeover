// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

// reajust values
#define STACK 2000
#define RELEASE 1750
#define SCORE 1500

namespace intake
{
     // Data functions.
     /*
     returns data regarding the intake's location.
     @return position: return average location of the intake.
     */
     int get_position(void);

     /*
     gives feedback regarding the movement of the intake.
     @return isStopped: return true if intake is stopped, else otherwise.
     */
     bool is_stopped(void);

     // Control functions.
     /*
     Sets the voltage of the intake motor
     @param voltage: the voltage to set the motor to
     */
     void set_voltage(int left_voltage, int right_voltage);

     // Autonomous functions.
     /**
     * Sends the intake to the position specified, can use predefined conditions
     * such as STACK, RELEASE, or SCORE.
     * @param posiition: Sends intake to specified position.
     * @param maxSpeed: Specifies the meximum speed when going to target.
     * @param wait: Defines the behavior of the function to act like a thread or function
     **/
     void move_to(int position, int max_speed, bool wait);

     // User control functions.
     /*
     Checks for action on the left bumpers to designate an intakeMode for the robot
     */
     void assign(void);

}// namespace intake
