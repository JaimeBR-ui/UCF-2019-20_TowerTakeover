// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// Filename: chassis.hpp

#include "main.h"

namespace chassis
{
     // Variables.
     extern bool was_moving;
     extern std::uint32_t now;
     extern int position_left, position_right;

     // Chassis Gains
     extern struct Gains * not_deployed;
     extern struct Gains * deployed;
     extern struct Gains * deployed_1cube;

     // Initialization
     /*
     Initializes the chassis components, allocates memory for the chassis gains.
     */
     void initialize(void);

     void reset(void);

     // Data functions.
     /*
     Gives the caller the current counts of the right side of the chassis.
     @return:
          Returns the raw counts of the Quadricature encoder.
     */
     int right_side_enc_units(void);

     /*
     Gives the caller the current counts of the left side of the chassis.
     @return:
          Returns the raw counts of the Quadricature encoder.
     */
     int left_side_enc_units(void);

     /*
     Gives the caller the average counts of the right side of the chassis.
     @return:
          Returns the raw counts of the Quadricature encoder.
     */
     int avg_enc_units(void);

     // Control functions.
     /*
     Sets the brake type of the chassi's motors.
     @param: mode
          Three modes:
               Hold - Holds robot at current target
               Brake - Brings robot to rest
               Coast - No intervention, lets robot coast to a stop.
     */
     void set_mode(pros::motor_brake_mode_e mode);

     /*
     Sets the voltege of the chassis. Ranges of parameters: -128 - 127.
     @param left_voltage:
          The 8 bit signed voltage int to set the left side.
     @param right_voltage:
          The 8 bit signed voltage int to set the right side.
     */
     void set_voltage(int left_voltage, int right_voltage);

     /*
     Sets the velocity of the chassis. Ranges of parameters: -200 - 200.
     Range depends on motor cartridge, in this case, we are using 200 rpm.
     @param left_velocity:
          Velocity int to set the left side.
     @param right_velocity:
          Velocity int to set the right side.
     */
     void set_velocity(int left_velocity, int right_velocity);

     /*
     Tares/resets/(sets to zero) all the encoders in the chassis.
     */
     void tare(void);

     /*
     Checks if the chassis is not moving.
     @return
          Returns true iff the chassis is at rest.
     */
     bool is_stopped(void);

     /*
     Sets the brake mode of the chassis to hold for a set amout of millis.
     @param millis:
          How long the chassi should stay in this more in ms.
     */
     void brake(int mills);

     // Autonomous functions.
     /*
     Moves the robot forward by the distance inputted.
     Uses the okapi motion profiler to generate a straight path.
     @param distance: distance in inches to travel forward.
     @param wait: waits for the robot to reach the target if true.
     */
     void forward(unsigned long long int distance, bool wait);

     /*
     Moves the robot backwards by the distance inputted.
     Uses the okapi motion profiler to generate a straight path.
     @param distance: distance in inches to travel backwards.
     @param wait: waits for the robot to reach the target if true.
     */
     void back(unsigned long long int distance, bool wait);

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
