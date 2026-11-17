#include "../include/PipelineEngine.hpp"
#include <iostream>

PipelineEngine::PipelineEngine(int capacity) : buffer(capacity) {
    
}

void PipelineEngine::start(int nAlpha, int capAlpha, int nBeta, int capBeta, int nGamma, int timeGamma) {    int total = nAlpha * capAlpha + nBeta * capBeta;
    buffer.start(total);

    for (int a = 0; a < nAlpha; a++) {
        // Alpha alpha(a, buffer, capAlpha);
        producers.push_back(std::make_unique<Alpha>(a + 1, buffer, capAlpha));
    }
    for (int b = 0; b < nBeta; b++) {
        // Beta beta(b, buffer, capBeta);
        producers.push_back(std::make_unique<Beta>(b + 1, buffer, capBeta));
    }
    for (int g = 0; g < nGamma; g++) {
        // Consumer consumer(g, buffer, capBeta);
        consumers.push_back(std::make_unique<Consumer>(g + 1, timeGamma, buffer));
    }

    for (size_t i = 0; i < producers.size(); i++) {
        pthread_t thread;
        int r = pthread_create(&thread, nullptr, producers[i]->enter, producers[i].get());
        if (r == 0) alphaBetaThreads.push_back(thread);
        else {
            std::cerr << "Error al crear el hilo del productor " << i + 1 << "\n"; 
            started = false;
        };
    }

    for (size_t i = 0; i < consumers.size(); i++) {
        std::thread thread(&Consumer::run, consumers[i].get());
        gammaThreads.push_back(std::move(thread));
    }
}

void PipelineEngine::waitAndJoin() {
    for (size_t i = 0; i < alphaBetaThreads.size(); i++) {
        pthread_join(alphaBetaThreads[i], nullptr);
    }

    for (size_t i = 0; i < gammaThreads.size(); i++) {
        gammaThreads[i].join();
    }
}

PipelineEngine::~PipelineEngine(){ waitAndJoin(); }