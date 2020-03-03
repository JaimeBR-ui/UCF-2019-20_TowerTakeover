// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// Filename: lift.hpp

#include "main.h"
#define MIN_POS 0
#define LOW_TOWER 1750
#define HIGH_TOWER 2900
#define ALLIANCE_TOWER 700
#define MAX_POS 3000
#define STACK_HEIGHT 500
#define OFF_GROUND 300

namespace lift
{
     // Variables.
     extern int was_moving;

     // Data functions.
     /*
     Gives the caller the current position of the lift.
     @return position: Returns the raw counts of the IME.
     */
     int get_position(void);

     /*
     Gives the caller a statement regarding the lifts movement.
     @return isStopped: Returns true iff the lift is not moving.
     */
     bool is_stopped(void);

     // Control funtions.
     /*
     Sets the voltage of the lift motor.
     @param voltage: the voltage to set the lift motor to.
     */
     void set_voltage(int voltage);

     // Autonomous functions.
     /*
     Moves the lift to a designated position on the lift's IME.
     @param position: the unit value to move the lift motor to, in raw counts.
     @param maxSpeed: the maximum allowable speed that the motor will move at.
     @param wait: waits to finish action if true.
     */
     void move_to(int position, int max_speed, bool wait = false);

     // User control functions.
     /*
     Assigns the movement of the lift based on the buttons pressed.
     */
     void assign(void);

}// namespace lift
