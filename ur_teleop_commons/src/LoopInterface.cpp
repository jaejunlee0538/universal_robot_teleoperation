//
// Created by ub1404 on 15. 8. 23.
//
#include <commons/utils/LoopInterface.h>
#include <iostream>

#define LOCK(mutex)     pthread_mutex_lock(&mutex)
#define UNLOCK(mutex)   pthread_mutex_unlock(&mutex)

struct sigaction LoopInterface::sigact;
bool LoopInterface::_should_stop = false;
bool LoopInterface::_is_signal_registered = false;
pthread_mutex_t LoopInterface::_lock_should_stop = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LoopInterface::_lock_is_signal_registered = PTHREAD_MUTEX_INITIALIZER;
pthread_t LoopInterface::thread_id;
std::vector<LoopInterface *> LoopInterface::instance_v;

LoopInterface::LoopInterface() {
    instance_v.push_back(this);

    LOCK(_lock_is_signal_registered);
    bool temp = _is_signal_registered;
    UNLOCK(_lock_is_signal_registered);
    if (!temp) {
        register_signal();
    }
}

LoopInterface::~LoopInterface() {

}

bool LoopInterface::should_stop() {
    LOCK(_lock_should_stop);
    bool temp = _should_stop;
    UNLOCK(_lock_should_stop);
    return temp;
}

void LoopInterface::register_signal() {
    LOCK(_lock_is_signal_registered);
    _is_signal_registered = true;
    LoopInterface::sigact.sa_handler = LoopInterface::__signal_handler;
    if (sigaction(SIGINT, &sigact, NULL)) {
        std::cerr << "sigaction(SIGIN) failed" << std::endl;
    }
    atexit(LoopInterface::destroy_mutex);
    UNLOCK(_lock_is_signal_registered);
}

void LoopInterface::destroy_mutex(void) {
    pthread_mutex_destroy(&_lock_should_stop);
    pthread_mutex_destroy(&_lock_is_signal_registered);
}

void LoopInterface::__signal_handler(int sig) {
    if (sig == SIGINT) {
        pthread_create(&thread_id, NULL, LoopInterface::_releasing_thread, NULL);
        if (!instance_v.empty()) {
            for (int i = 0; i < instance_v.size(); i++) {
                instance_v[i]->signal_handler(sig);
            }
        }
    }
}

void *LoopInterface::_releasing_thread(void *args) {
    LOCK(_lock_should_stop);
    _should_stop = true;
    UNLOCK(_lock_should_stop);
}