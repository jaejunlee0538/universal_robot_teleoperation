//
// Created by ub1404 on 15. 8. 25.
//

#ifndef UR5_ELAPSEDTIME_H
#define UR5_ELAPSEDTIME_H

#include <sys/time.h>

class ElapsedTime {
public:
    ElapsedTime() {
        gettimeofday(&t0, 0);
    }

    void start() {
        gettimeofday(&t0, 0);
    }

    long int getElapsed_usec(bool print = false) {
        gettimeofday(&t1, 0);
        timersub(&t1, &t0, &t_elapsed);
        if (print) {
            printf("Elapsed : %ld usec\n", t_elapsed.tv_sec * 1000000 + t_elapsed.tv_usec);
        }
        return t_elapsed.tv_sec * 1000000 + t_elapsed.tv_usec;
    }

    long int getElapsed_msec(bool print = false) {
        gettimeofday(&t1, 0);
        timersub(&t1, &t0, &t_elapsed);
        if (print) {
            printf("Elapsed : %ld msec\n", t_elapsed.tv_sec * 1000 + t_elapsed.tv_usec / 1000);
        }
        return t_elapsed.tv_sec * 1000 + t_elapsed.tv_usec / 1000;
    }

    double getElapsed_sec(bool print = false) {
        gettimeofday(&t1, 0);
        timersub(&t1, &t0, &t_elapsed);
        if (print) {
            printf("Elapsed : %lf.6 sec\n", t_elapsed.tv_sec + t_elapsed.tv_usec / 1000000.0);
        }
        return t_elapsed.tv_sec + t_elapsed.tv_usec / 1000000.0;
    }

private:
    timeval t0, t1, t_elapsed;
};

#endif //UR5_ELAPSEDTIME_H
