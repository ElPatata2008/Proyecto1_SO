#ifndef CONSUMER_H_
#define CONSUMER_H_

#include "SharedBuffer.hpp"

class Consumer {
private:
    int _id;
    int _gammaTime = 0;
    SharedBuffer& _buffer;

    static constexpr int timePenalty = 4;
public:
    Consumer(int id, int time, SharedBuffer& buffer);
    void run();
};

#endif