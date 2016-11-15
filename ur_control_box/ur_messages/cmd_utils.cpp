//
// Created by ub1404 on 15. 8. 24.
//
#include "cmd_utils.h"

bool compareDoubles(const double &a, const double &b) {
    double diff = fabs(a - b);
    if (diff < std::numeric_limits<double>::min())
        return true;
    if (diff < std::numeric_limits<double>::epsilon() * fabs(a + b) * 2)
        return true;
    return false;
}