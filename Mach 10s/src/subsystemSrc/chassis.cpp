// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

#define SLOWDOWN_FACTOR 2
#define TURN_CONSTANT 0.75
#define POINT_TURN_CONSTANT 1.5

namespace chassis
{
     // Variables
     int position_left, position_right;

     // Data functions.
     int avg_right_side_enc_units(void)
     {
          return back_right.get_position();
     }

     int avg_left_side_enc_units(void)
     {
          return back_left.get_position();
     }

     int get_max_temperature(void)
     {
          int retval = front_left.get_temperature();

          if (retval < front_right.get_temperature())
               retval = front_right.get_temperature();
          if (retval < back_right.get_temperature())
               retval = back_right.get_temperature();
          if (retval < back_left.get_temperature())
               retval = back_left.get_temperature();

          return retval;
     }

     int avg_enc_units(void)
     {
          return (avg_right_side_enc_units() +
                  avg_left_side_enc_units()) / 2;
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
          set_velocity(0, 0);
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

     void turn(int degrees_10, int max_percent, int accuracy_timer)
     {
          // Rotates robot using encoder counts.
          // Max Linear Vel : 1.064 m/s.
          // Max Linear Accel : 2 m/s/s;
          int velocity_l = 0, velocity_r = 0;
          int max_velocity = 120, min_velocity = 20;
          int target = degrees_10 * TURN_CONSTANT;
          int reverse = abs(target) / target;

          double proportional = 0.16, integral = 0.0001;
          double ratio = max_percent / 100;
          double error_l = 0.0, error_r = 0.0;
          double sum_integral_r = 0, sum_integral_l = 0;

          set_mode(MOTOR_BRAKE_COAST);
          set_voltage(0, 0);
          tare();
          {
               // Just some constant acceleration to prevent initial slippage.
               // Independent from encoder counts.
               std::cout << "Ran turn code" << std::endl;
               for (int i = 0; i < max_velocity; i+=2)
               {
                    velocity_l = (reverse * i * ratio);
                    std::cout << "vel: " << velocity_l << std::endl;
                    set_velocity(velocity_l, -velocity_l);
                    pros::delay(10);
               }

               velocity_r = velocity_l;

               std::cout << "ended for loop, going into while loop" << std::endl;
               std::cout << "left right" << std::endl;
               std::cout << velocity_l << "  " << velocity_r << std::endl;
          }
          int count = 0;
          while (velocity_l != 0 || velocity_r != 0) // velocity_l != 0 || velocity_r != 0
          {
               std::cout << "iteration: " << count << std::endl;

               error_l = target - avg_left_side_enc_units();
               error_r = target + avg_right_side_enc_units();

               sum_integral_l += error_l * integral;
               sum_integral_r += error_r * integral;

               // Integral and proportional applied.
               velocity_l = proportional * error_l ;//+ sum_integral_l;
               velocity_r = proportional * error_r ;//+ sum_integral_r;
               {
                    if (velocity_l > max_velocity)
                         velocity_l = max_velocity;

                    if (velocity_r > max_velocity)
                         velocity_r = max_velocity;

                    std::cout << "left right" << std::endl;
                    std::cout << velocity_l << "  " << velocity_r << std::endl;
               }
               set_velocity(velocity_l, -velocity_r);
               pros::delay(20);
               count++;
          }
          std::cout << "ended while loop" << std::endl;
          brake(accuracy_timer); // maybe i dont need this
     }

     void pointTurn(int degrees_10, int max_speed, int accuracy_timer)
     {
          return;
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
               r = (int) r / SLOWDOWN_FACTOR;
          }

          if (l != 0 || r != 0)
               set_voltage(l, r);
          else
               set_voltage(0, 0);
          //print_sensors();
           lv_gauge_set_value(gauge1, 1, get_max_temperature());

     }
}// namespace chassis
