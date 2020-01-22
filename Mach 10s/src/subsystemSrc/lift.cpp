// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// File: lift.cpp

#include "main.h"

#define MAX_VOLTAGE 110

namespace lift
{
     // Variables.
     int was_moving = 1;
     int lift_position_left = 0;
     int lift_position_right = 0;
     std::uint32_t now = pros::millis();

     // Data Functions.
     int get_position(void)
     {
          now = pros::millis();
          return (lift_left.get_raw_position(&now) +
                  lift_left.get_raw_position(&now)) / 2;
     }

     bool is_stopped(void)
     {
          return lift_left.is_stopped()
             && lift_right.is_stopped();
     }

     int get_max_temperature(void)
     {
          return (lift_left.get_temperature() > lift_right.get_temperature())
               ? lift_left.get_temperature()
               : lift_right.get_temperature();
     }

     // Control Functions.
     void set_voltage(int voltage)
     {
          lift_left = voltage;
          lift_right = voltage;
     }

     void tare(void)
     {
          lift_left.tare_position();
          lift_right.tare_position();
     }

     void set_mode(pros::motor_brake_mode_e mode)
     {
          lift_left.set_brake_mode(mode);
          lift_right.set_brake_mode(mode);
     }

     //Autonomous Functions
     void hold_position(void)
     {
          set_voltage(0);
          set_mode(MOTOR_BRAKE_HOLD);
          lift_position_left = (lift_left.get_raw_position(&now) > 0)
               ? lift_left.get_raw_position(&now)
               : 0;
          lift_position_right = (lift_right.get_raw_position(&now) > 0)
               ? lift_right.get_raw_position(&now)
               : 0;
          if (was_moving == 1){
               lift_left.move_absolute(lift_position_left, 127);
                    lift_right.move_absolute(lift_position_right, 127);
                    was_moving = 0;
               return;
          }
          /*//why do this when I can just lower the speed lol
          set_mode(MOTOR_BRAKE_COAST);
          for(int i = 0; i < 64; i++){//slows down to prevent possible gear skip
          set_voltage(i);
          pros::delay(50);
          }
          set_mode(MOTOR_BRAKE_HOLD);
          */
          int max_speed = 60;
          lift_left.move_absolute(lift_position_left, max_speed);
          lift_right.move_absolute(lift_position_right, max_speed);
          was_moving = 0;
     }

     void move_to(int position, int max_speed, bool wait)
     {
          lift_left.move_absolute(position, max_speed);
          lift_right.move_absolute(position, max_speed);

          if (position - get_position() > 0)
               was_moving = 1;
          else
               was_moving = -1;

          if (wait && pros::competition::is_autonomous())
               while (fabs(position - get_position()) > 10)
                    pros::delay(20);
          else if (wait)
               while (fabs(position - get_position()) > 10)
               {

                    intake::assign();
               }
     }

     //User Control Functions
     void assign(void)
     {
          if (controller_digital(A))
               move_to(MAX_POS, MAX_VOLTAGE, true);
          else if (controller_digital(B))
               move_to(ALLIANCE_TOWER, MAX_VOLTAGE, true);
          else if (controller_digital(X))
               move_to(HIGH_TOWER, MAX_VOLTAGE, true);
          else if (controller_digital(Y))
               move_to(LOW_TOWER, MAX_VOLTAGE, true);
          else if (controller_digital(LIFT_SHIFTER_UP))
          {
               set_mode(MOTOR_BRAKE_COAST);
               if(get_position() < 0)
               {
                    set_voltage(-40);
               }
               else if(get_position() < 107)
                    set_voltage(-(get_position()+20));
               else
                    set_voltage(-MAX_VOLTAGE);
               was_moving = -1;
          }
          else if (controller_digital(LIFT_SHIFTER_DOWN) && get_position() < 3000)
          {
               set_mode(MOTOR_BRAKE_COAST);
               if (get_position() > 2873)
                    set_voltage(3000 - get_position());
               else
                    set_voltage(MAX_VOLTAGE);
               was_moving = 1;
          }
          else if (was_moving != 0)
               hold_position();

          lv_gauge_set_value(gauge1, 2, get_max_temperature());
     }
}// namespace lift
