// Author(s): Jaime Bohorquez
// Copyright (c) 2019-2020, Knightmare Engineering Club.
// Programmed using Atom + Terminal on Mac OS
// Filename: path.hpp

#include "main.h"

using namespace okapi;

namespace chassis
{
     namespace path
     {
          // Data functions.
          bool is_settled(void);

          // Path functions.
          void move_to(std::initializer_list<Point>);

          void make(std::initializer_list<Point>, std::string);

          void remove(std::string id);

          void wait_until_settled();

          void set(std::string id, bool backwards = false);
     }// namespace path
}// namespace chassis
