// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"
#define SLOWDOWN_FACTOR 2
#define TURN_CONSTANT 0.75
#define POINT_TURN_CONSTANT 1.5

namespace chassis
{
     // Variables.
     extern int position_left, position_right;
     extern std::uint32_t now;
     extern bool was_moving;

     // Data functions.
     double avg_right_side_enc_units(void);

     double avg_left_side_enc_units(void);

     double avg_enc_units(void);

     double avg_turning_enc_units(void);

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

     void turn(int degrees_10, int max_speed, int accuracy_timer);

     void point_turn(int degrees_10, int max_speed, int accuracy_timer);

     // User control functions.
     void assign(void);
     
}// namespace chassis
