//
// Created by ub1404 on 15. 8. 18.
//

#ifndef UR5_CMD_UTILS_H
#define UR5_CMD_UTILS_H

#include <limits.h>
#include <cmath>
#include <limits>

#define SET_BIT_COND(in, val, pos)      (in |= (val<<pos))
#define SET_BIT(in, pos)                (in |= 1<<pos)
#define CLEAR_BIT(in, pos)              (in &= ~(1<<pos))
#define GET_BIT(val, pos)               ((bool)(val & (1<<pos)))


bool compareDoubles(const double &a, const double &b);

#endif //UR5_CMD_UTILS_H
