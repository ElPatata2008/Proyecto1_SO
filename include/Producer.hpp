#ifndef PRODUCER_H_
#define PRODUCER_H_

#include "SharedBuffer.hpp"

class Producer {
private:
    char _type;
    int _id;
    int _pkgAmount;
    SharedBuffer& _buffer;

    int counter = 0;

    static constexpr int maxProcess = 5;
    static constexpr int sleepTime = 16;
public:
    Producer(char type, int id, SharedBuffer& buffer, int amount);
    void run();
    virtual ~Producer();
    static void* enter(void*);
protected:
    virtual void computeOne() = 0;
};

class Alpha : public Producer {
private:
    std::vector<float> data;
    const int nVertices = 1000;
public:
    Alpha(int id, SharedBuffer& buffer, int amount);
protected:
    void computeOne() override;
};

class Beta : public Producer {
public:
    Beta(int id, SharedBuffer& buffer, int amount);
protected:
    void computeOne() override;
};

#endif