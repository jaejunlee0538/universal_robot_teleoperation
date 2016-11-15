//
// Created by ub1404 on 15. 9. 7.
//

#ifndef ROBOTCONTROL_CVSOSTREAM_H
#define ROBOTCONTROL_CVSOSTREAM_H

#include <iostream>
#include <fstream>

class CSVOstream {
public:
    std::ostream &os;
    bool new_line;
public:
    CSVOstream(std::ostream &o) : os(o), new_line(true) { }

    template<class T>
    CSVOstream &operator<<(T const &t) {
        if (!new_line)
            os << ",";
        os << t;
        new_line = false;
        return *this;
    }

    CSVOstream &operator<<(std::ostream &(*manip)(std::ostream &)) {
        if (manip == static_cast<std::ostream &(*)(std::ostream &)>(std::endl)) {
            reset();
        }
        manip(os);
        return *this;
    }

    void reset() { new_line = true; }

    operator void *() { return (void *) os; }
};


#endif //ROBOTCONTROL_CVSOSTREAM_H
