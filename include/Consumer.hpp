#ifndef CONSUMER_H_
#define CONSUMER_H_

#include "SharedBuffer.hpp"

class Consumer {
private:
    int _gammaTime = 0;
    int _dispatch = 0;
    SharedBuffer& _buffer;

    int amountDispatched = 0;
    const int timePenalty = 4;
public:
    Consumer(int amount, int time, SharedBuffer& buffer);
    void run();
    static void* enter(void*);
};

#endif