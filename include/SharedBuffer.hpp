#ifndef SHAREDBUFFER_H_
#define SHAREDBUFFER_H_

#include "Package.hpp"
#include <queue>
#include <pthread.h>
#include <cstddef>

struct PopResult {
    Package pkg;
    int remain = 0;
    bool underflow = false;
    bool done = false;
};

class SharedBuffer {
private:
    size_t _queueCapacity;
    std::queue<Package> pkgQueue;
    
    int _consumed = 0;
    int _totalProyected = 0;
    bool _pipelineActive = false;

    int _nextIdAlpha = 1;
    int _nextIdBeta = 1;

    pthread_mutex_t m;
    pthread_cond_t notFull;
    pthread_cond_t notEmpty;
public:
    SharedBuffer(const SharedBuffer&) = delete;
    SharedBuffer& operator=(const SharedBuffer&) = delete;

    SharedBuffer(size_t cap);

    void start(int total);
    void shutdown();

    void push(char type); 
    PopResult pop();
    bool completed() { return _consumed == _totalProyected; };

    ~SharedBuffer();
};


#endif