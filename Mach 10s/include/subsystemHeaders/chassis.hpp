// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

namespace chassis
{
     // Variables.
     extern int position_left, position_right;
     extern std::uint32_t now;
     extern bool was_moving;

     // Chassis Gains
     extern struct Gains * not_deployed;
     extern struct Gains * deployed;
     extern struct Gains * deployed_1cube;

     // Initialization
     void initialize(void);

     // Data functions.
     int avg_right_side_enc_units(void);

     int avg_left_side_enc_units(void);

     int avg_enc_units(void);

     int avg_turning_enc_units(void);

     // Control functions.
     void set_mode(pros::motor_brake_mode_e);

     void set_voltage(int left_voltage, int right_voltage);

     void set_velocity(int left_velocity, int right_velocity);

     void turn_to_target(int target, int max_speed);

     void tare(void);

     bool is_stopped(void);

     void brake(int mills);

     // Autonomous functions.
     void forward(unsigned long long int distance, bool wait);

     void back(unsigned long long int distance, bool wait);

     void point_turn(int degrees_10, int max_speed, int accuracy_timer);

     /*
 Turns the robot the desired amount.
 @param degrees_10:
       target angle multiplied by 10. Ex: turn 90 deg, degrees_10 = 900
 @param accuracy_timer:
       Timer that tells the function to end after the specified time in ms.
 @param gain:
       This is a struct that contains the PID gains required to turn.
       Fields of the Gains struct:
            double Kp - Proportional gain.
            double Ki - Integral gain.
            double Kd - Derivative gain.
 @return: returns 0 if accuracy_timer forced ended the turn.
 */
 void turn(int degrees_10, int accuracy_timer, struct Gains * gain);

 // User control functions.
 /*
 Thread that runs the teleoperated program for the chassis
 */
 void assign(void * ignore);

}// namespace chassis
