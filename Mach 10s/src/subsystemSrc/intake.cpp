// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS

#include "main.h"

namespace intake
{
     // Variables
     enum intake_modes
     {
          INTAKE_MODE_STACK = 0,
          INTAKE_MODE_RELEASE = 1,
          INTAKE_MODE_SCORE = 2,
          INTAKE_MODE_STORED = 3
     };

     // Starting position of intake.
     int intake_mode = INTAKE_MODE_STORED;
     int intake_power = 63;
     bool was_moving = true;
     std::uint32_t now = pros::millis();

     // Data Functions
     int get_position(void)
     {
          return (intake_left.get_position() +
                 intake_right.get_position()) / 2;
     }

     bool is_stopped(void)
     {
          return intake_right.is_stopped()
               && intake_left.is_stopped();
     }

     bool changed_to_pressed(std::int32_t a)
     {
          static int last_value = 0;
          static int new_value = 0;
          last_value = new_value;
          if(a == 0)
               new_value = 0;
          else
               new_value = 1;
          return new_value == 1 && last_value == 0;
     }

     int get_max_temperature(void)
     {
          return (intake_right.get_temperature() > intake_left.get_temperature())
               ? intake_right.get_temperature()
               : intake_left.get_temperature();
     }

     // Control Functions
     void set_mode(pros::motor_brake_mode_e mode)
     {
          intake_right.set_brake_mode(mode);
          intake_left.set_brake_mode(mode);
     }

     void set_voltage(int voltage)
     {
          intake_left = voltage;
          intake_right = voltage;
     }

     void set_velocity(int leftVel, int rightVel)
     {
          intake_left.move_velocity(leftVel);
          intake_right.move_velocity(rightVel);
     }

     void tare(void)
     {
          intake_left.tare_position();
          intake_right.tare_position();
     }

     // Autonomous Functions
     void move_to(int position, int max_speed, bool wait)
     {
          set_mode(MOTOR_BRAKE_HOLD);
          intake_left.move_absolute(position, max_speed);
          intake_right.move_absolute(position, max_speed);

          if (wait && pros::competition::is_autonomous())
               while (fabs(position - get_position()) > 200)
                    pros::delay(20);

          else if (wait)
               while (fabs(position - get_position()) > 10)
               {
                    chassis::assign();
                    lift::assign();
               }
     }

     void hold_position(void)
     {
          int max_speed = 127, position_left, position_right;
          set_voltage(0);
          set_mode(MOTOR_BRAKE_HOLD);
          position_left = intake_left.get_raw_position(&now);
          position_right = intake_right.get_raw_position(&now);
          intake_left.move_absolute(position_left, max_speed);
          intake_right.move_absolute(position_right, max_speed);
          was_moving = false;
     }

     // User Control Functions
     void set_intake_mode(int mode)
     {
          switch (mode)
          {
               case INTAKE_MODE_STACK:
                    move_to(STACK, 127, false);
                    break;
               case INTAKE_MODE_RELEASE:
                    move_to(RELEASE, 127, false);
                    break;
               case INTAKE_MODE_SCORE:
                    move_to(SCORE, 127, false);
                    break;
          }
     }

     void assign(void)
     {
          if (controller_digital(INTAKE))
          {
               set_mode(MOTOR_BRAKE_COAST);
               set_voltage(-intake_power);
               was_moving = true;
          }
          else if (controller_digital(OUTTAKE))
          {
               set_mode(MOTOR_BRAKE_COAST);
               set_voltage(intake_power);
               was_moving = true;
          }
          else if (was_moving)
               hold_position();

          lv_gauge_set_value(gauge1, 0, get_max_temperature());
     }
}// namespace intake
