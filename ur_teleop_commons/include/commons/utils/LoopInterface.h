//
// Created by ub1404 on 15. 8. 23.
//
/*
 * http://www.cplusplus.com/reference/atomic/
 * http://stackoverflow.com/questions/32166135/is-this-interface-thread-safe/32166223#32166223
 */
#ifndef UR5_LOOPINTERFACE_H
#define UR5_LOOPINTERFACE_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <vector>

/*
 * Supports multiple instances.
 * When SIGINT is signaled, each signal_handler method of all LoopInterface instances are called.
 */
class LoopInterface {
public:
    LoopInterface();

    ~LoopInterface();

    bool should_stop();

protected:
    virtual void signal_handler(int sig) {

    }

private:
    static struct sigaction sigact;

    static void register_signal();

    static void destroy_mutex(void);

    static void __signal_handler(int sig);

    static void *_releasing_thread(void *args);

    static bool _should_stop;
    static bool _is_signal_registered;
    static pthread_mutex_t _lock_should_stop, _lock_is_signal_registered;
    static pthread_t thread_id;
    static std::vector<LoopInterface *> instance_v;  //TODO : instance_v is not safe under multi-thread
};


#endif //UR5_LOOPINTERFACE_H
