#ifndef SHAREDBUFFER_H_
#define SHAREDBUFFER_H_

#include "Package.hpp"
#include <queue>
#include <pthread.h>

struct PopResult {
    Package pkg;
    int remain;
    bool underflow;
};

class SharedBuffer {
private:
    int _queueCapacity;
    std::queue<Package> pkgQueue;
    pthread_mutex_t m;
    pthread_cond_t notFull;
    pthread_cond_t notEmpty;
public:
    SharedBuffer(int cap);
    void push(Package pkg); 
    PopResult pop();

    ~SharedBuffer();
};


#endif