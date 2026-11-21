#include "../include/PipelineEngine.hpp"
#include <iostream>
#include <system_error>

PipelineEngine::PipelineEngine(int capacity) : buffer(capacity) {
    
}

int PipelineEngine::start(int nAlpha, int capAlpha, int nBeta, int capBeta, int nGamma, int timeGamma) {    
    int total = nAlpha * capAlpha + nBeta * capBeta;
    if (started) return 1; 

    bool anyNegatives = nAlpha < 0 || capAlpha < 0 || nBeta < 0 || capBeta < 0 || nGamma < 0 || timeGamma < 0;
    bool nAlpha0 = nAlpha > 0 && capAlpha > 0;
    bool nBeta0 = nBeta > 0 && capBeta > 0;
    bool validValues = nAlpha + nBeta > 0 && ((nAlpha0 && !nBeta0) || (!nAlpha0 && nBeta0));
    if (!anyNegatives && validValues) return 2;

    buffer.start(total);

    for (int a = 0; a < nAlpha; a++) 
        producers.push_back(std::make_unique<Alpha>(a + 1, buffer, capAlpha));
    
    for (int b = 0; b < nBeta; b++) 
        producers.push_back(std::make_unique<Beta>(b + 1, buffer, capBeta));
    
    for (int g = 0; g < nGamma; g++) 
        consumers.push_back(std::make_unique<Consumer>(g + 1, timeGamma, buffer));
    
    started = true;

    for (size_t i = 0; i < producers.size(); i++) {
        pthread_t thread;
        int r = pthread_create(&thread, nullptr, producers[i]->enter, producers[i].get());
        if (r == 0) alphaBetaThreads.push_back(thread);
        else { buffer.shutdown(); return 3; }
    }

    for (size_t i = 0; i < consumers.size(); i++) {
        std::thread thread;
        try { thread = std::thread(&Consumer::run, consumers[i].get()); }
        catch (const std::system_error& e) {
            std::cerr << "ERROR: " << e.what() << "\n";
            buffer.shutdown();
            return 4;
        }
        gammaThreads.push_back(std::move(thread));
    }

    return 0;
}

void PipelineEngine::waitAndJoin() {
    if (!alphaBetaThreads.empty()) {
        for (size_t i = 0; i < alphaBetaThreads.size(); i++) {
            pthread_join(alphaBetaThreads[i], nullptr);
        }
        alphaBetaThreads.clear();
    }
    if (!gammaThreads.empty()) {
        for (size_t i = 0; i < gammaThreads.size(); i++) {
            if (gammaThreads[i].joinable()) gammaThreads[i].join();
        }
        gammaThreads.clear();
    }
}

PipelineEngine::~PipelineEngine(){ waitAndJoin(); }