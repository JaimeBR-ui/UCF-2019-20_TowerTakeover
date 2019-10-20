// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

namespace chassis
{
     // Variables
     int position_left, position_right;
     std::uint32_t now = pros::millis();

     // Data functions.
     int avg_right_side_enc_units(void)
     {
          now = pros::millis();
          return (front_right.get_raw_position(&now) +
          back_right.get_raw_position(&now)) / 2;
     }

     int avg_left_side_enc_units(void)
     {
          now = pros::millis();
          return (front_left.get_raw_position(&now) +
                  back_left.get_raw_position(&now)) / 2;
     }

     int avg_enc_units(void)
     {
          return (avg_right_side_enc_units() +
                  avg_left_side_enc_units()) / 2;
     }

     int avg_turning_enc_units(void)
     {
          int a = abs(back_left.get_position())
               + abs(front_left.get_position())
               + abs(back_right.get_position())
               + abs(front_right.get_position());
          return a/4;
     }

     void print_sensors(void)
     {
          printf("Left side average:  %d\n", avg_left_side_enc_units());
          printf("Right side average: %d\n", avg_right_side_enc_units());
     }

     bool is_stopped(void)
     {
          return front_right.is_stopped()
          && back_right.is_stopped()
          && front_left.is_stopped()
          &&  back_left.is_stopped();
     }

     // Control functions.
     void set_mode(pros::motor_brake_mode_e mode)
     {
          front_right.set_brake_mode(mode);
          back_right.set_brake_mode(mode);
          front_left.set_brake_mode(mode);
          back_left.set_brake_mode(mode);
     }

     void set_voltage(int left_voltage, int right_voltage)
     {    // Sets drive voltage to an 8 bit signed integer.
          back_right = right_voltage;
          front_right = right_voltage;
          back_left = left_voltage;
          front_left = left_voltage;
     }

     void set_velocity(int left_velocity, int right_velocity)
     {    // Sets chassis velocity.
          front_right.move_velocity(right_velocity);
          back_right.move_velocity(right_velocity);
          front_left.move_velocity(left_velocity);
          back_left.move_velocity(left_velocity);
     }

     void turn_to_target(int target, int max_speed)
     {    // Chassis goes to encoder target when turning.
          back_left.move_absolute(target, max_speed);
          front_left.move_absolute(target, max_speed);
          back_right.move_absolute(-target, max_speed);
          front_right.move_absolute(-target, max_speed);
     }

     void tare(void)
     {    // Sets chassis encoders to zero.
          front_left.tare_position();
          back_left.tare_position();
          front_right.tare_position();
          back_right.tare_position();
     }

     void brake(int mills)
     {    // Brakes drive for set amount of milliseconds.
          set_mode(MOTOR_BRAKE_HOLD);
          pros::delay(mills);
          set_mode(MOTOR_BRAKE_COAST);
     }

     void move_to(int target_right, int target_left, int max_speed)
     {
          set_mode(MOTOR_BRAKE_HOLD);
          back_right.move_absolute(target_right, max_speed);
          front_right.move_absolute(target_right, max_speed);
          back_left.move_absolute(target_left, max_speed);
          front_left.move_absolute(target_left, max_speed);
     }

     void hold_position(void)
     {
          position_right = avg_right_side_enc_units();
          position_left = avg_left_side_enc_units();
          move_to(position_right, position_left, 127);
     }

     // Autonomous functions.
     void forward(unsigned long long distance, bool wait)
     {
          path::move_to({
                    point::start,
                    point::make(distance, 0, 0)
               }
          );
          if (wait)
               path::wait_until_settled();
     }
     void back(unsigned long long distance, bool wait)
     {
          path::make({
                    point::start,
                    point::make(distance, 0, 0)
               },
               "temp"
          );
          path::set("temp", true);
          if (wait)
          {
               path::wait_until_settled();
               path::remove("temp");
          }
     }

     void turn(int degrees_10, int max_velocity, int accuracy_timer)
     {
          // Rotates robot using encoder counts.
          int speed = 0;
          int min_velocity = 32;
          int target = degrees_10 * 0.75;
          float proportional = 0.30;
          float error = 0.0, ratio, ratio_const = 0.18;
          int reverse = abs(target) / target;
          int distance_to_speed_up = target * 0.2;

          set_mode(MOTOR_BRAKE_COAST);
          set_voltage(0, 0);
          tare();

          while (avg_turning_enc_units() < abs(distance_to_speed_up))
          {
               if (avg_turning_enc_units() / abs(distance_to_speed_up) >= ratio_const)
                    ratio = avg_turning_enc_units() / abs(distance_to_speed_up);
               else
                    ratio_const = 0.18;

               speed = max_velocity * ratio * reverse;

               set_velocity(speed, -speed);
               pros::delay(20);
          }

          while (abs(avg_turning_enc_units() - target) > 25)
          {
               error = target - avg_turning_enc_units();

               speed = proportional * error;

               if (speed > max_velocity)
                    speed = max_velocity;

               else if (speed < min_velocity)
                    speed = min_velocity;

               set_velocity(speed, -speed);
               pros::delay(20);
          }

          turn_to_target(target, 20);

          pros::delay(accuracy_timer);
          set_voltage(0, 0);
     }

     void pointTurn(int degrees_10, int max_speed, int accuracy_timer)
     {    // Skip to line 278, this is not readable so don't attempt to!
          /* Rotates chassis using encoder counts with one side stopped
          // Part of development, point turning is more accurate, but slower.
int target = degrees_10 * POINT_TURN_CONSTANT;
float proportional = 0.18, error = 0.0, ratio;
int speed = 0;
int reverse = abs(target) / target;
int distance_to_speed_up = target * 0.2 * 900 / degrees_10;
tare();
if (target > 0)
{    // If we are turning right
back_right.move_absolute(0, max_speed);
front_right.move_absolute(0, max_speed);
while (avg_left_side_enc_units() < abs(distance_to_speed_up))
{
ratio = (avg_left_side_enc_units() / abs(distance_to_speed_up) >= 0.15)
? avg_left_side_enc_units() / abs(distance_to_speed_up)
: 0.15;
speed = max_speed * ratio * reverse * 1.57;
if (speed>200)
speed = 200;
else if (speed< -200)
speed = -200;
front_left.move_velocity(speed);
back_left.move_velocity(speed);
pros::delay(20);
/*printf("rotateEncoder(); loop2; avg_turning_enc_units(): %f; target: \
%d; speed: %d;\n", avg_left_side_enc_units(), target,speed);/
}
while (avg_left_side_enc_units() > target + 50
|| avg_left_side_enc_units() < target - 50)
{
error = target - avg_left_side_enc_units();
speed = (proportional * error > 127)
? 127
: proportional * error;
speed = (speed >= 20)? speed: 20;
speed = speed * 1.57;
front_left.move_velocity(speed);
back_left.move_velocity(speed);
/*printf("rotateEncoder(): avg_turning_enc_units(): %f; target: %d; \
speed: %d;\n", \
avg_left_side_enc_units(), target,speed);/
pros::delay(20);
}
back_left.move_absolute(target, 20);
front_left.move_absolute(target, 20);
}
else
{    // If we are turning left
back_left.move_absolute(0, max_speed);
front_left.move_absolute(0, max_speed);
while (avg_right_side_enc_units() < abs(distance_to_speed_up))
{
ratio = (avg_right_side_enc_units() / abs(distance_to_speed_up) >= 0.15)
? avg_right_side_enc_units() / abs(distance_to_speed_up)
: 0.15;
speed = max_speed * ratio * reverse * 1.57;
if (speed > 200)
speed = 200;
else if (speed < -200)
speed = -200;
front_right.move_velocity(speed);
back_right.move_velocity(speed);
pros::delay(20);
/*printf("rotateEncoder(); loop2; avg_turning_enc_units(): %f; target: \
%d; speed: %d;\n", \
avg_right_side_enc_units(), target,speed);/
}
while (avg_right_side_enc_units() > target + 50
|| avg_right_side_enc_units() < target - 50)
{
error = target - avg_right_side_enc_units();
speed = (proportional * error > 127)
? 127
: proportional * error;
speed = (speed >= 20)? speed: 20;
speed = speed * 1.57;
front_right.move_velocity(speed);
back_right.move_velocity(speed);
/*printf("rotateEncoder(): avg_turning_enc_units(): %f; target: \
%d; speed: %d;\n", \
avg_right_side_enc_units(), target,speed);/
pros::delay(20);
}
back_right.move_absolute(target, 20);
front_right.move_absolute(target, 20);
}
pros::delay(accuracy_timer);
set_voltage(0, 0);*/
     }

     // User control functions.
     void assign(void)
     {
          // Assigns voltage with deadband
          int l = controller_analog(LEFT_JOYSTICK);
          int r = controller_analog(RIGHT_JOYSTICK);

          l = (abs(l) > 10) ? l: 0;
          r = (abs(r) > 10) ? r : 0;

          if (lift::get_position() > 1000)
          {
               // Should be created into a smooth decrease.
               l = (int) l / SLOWDOWN_FACTOR;
               r = (int) l / SLOWDOWN_FACTOR;
          }

          if (l != 0 || r != 0)
               set_voltage(l, r);
          else
               set_voltage(0, 0);
          print_sensors();
     }
}// namespace chassis
