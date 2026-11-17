#ifndef PIPELINEENGINE_H_
#define PIPELINEENGINE_H_

#include "SharedBuffer.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include <vector>
#include <memory>
#include <thread>

class PipelineEngine {
private:
    SharedBuffer buffer;
    std::vector<std::unique_ptr<Producer>> producers;
    std::vector<std::unique_ptr<Consumer>> consumers;
    std::vector<pthread_t> alphaBetaThreads;
    std::vector<std::thread> gammaThreads;
    bool started = false;
public:
    PipelineEngine(int capacity);
    void start(int nAlpha, int capAlpha, int nBeta, int capBeta, int nGamma, int timeGamma);
    void waitAndJoin();
    ~PipelineEngine();
};

#endif