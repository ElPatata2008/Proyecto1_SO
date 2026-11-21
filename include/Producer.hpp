#ifndef PRODUCER_H_
#define PRODUCER_H_

#include "SharedBuffer.hpp"
#include <cmath>

class Producer {
private:
    char _type;
    int _id;
    SharedBuffer& _buffer;
    int _pkgAmount;

    int counter = 0;

    static constexpr int maxProcess = 5;
    static constexpr int sleepTime = 16;
public:
    Producer(char type, int id, SharedBuffer& buffer, int amount);
    void run();
    virtual ~Producer();
    static void* enter(void*);
protected:
    virtual bool computeOne() = 0;
};

class Alpha : public Producer {
private:
    std::vector<float> data;
    float angle;
    static constexpr int nVertices = 1000;
public:
    Alpha(int id, SharedBuffer& buffer, int amount);
    float radiansToDegree(float rad) {
        const double PI = std::acos(-1.0);
        return rad * (180.0 / PI);
    }
protected:
    bool computeOne() override;
};

class Beta : public Producer {
private:
    std::vector<float> data;
    static constexpr int n = 1000000;
public:
    Beta(int id, SharedBuffer& buffer, int amount);
protected:
    bool computeOne() override;
};

#endif