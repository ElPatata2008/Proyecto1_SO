#ifndef PRODUCER_H_
#define PRODUCER_H_

#include "SharedBuffer.hpp"
#include <vector>

class Producer {
private:
    char _type;
    std::vector<int> _times;
    SharedBuffer& _buffer;

    int counter = 0;

    const int maxProcess = 5;
    const int sleepTime = 16;
public:
    Producer(char type, SharedBuffer& buffer, const std::vector<int>& times);
    void run();
    static void* enter(void*);
};

#endif