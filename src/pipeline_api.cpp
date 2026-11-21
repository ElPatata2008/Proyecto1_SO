#include "../include/pipeline_api.h"
#include "../include/PipelineEngine.hpp"
#include <iostream>

static PipelineEngine* engine = NULL;

int pipeline_init(size_t capacidad_buffer) {
    try {
        if (engine == NULL) {
            if (capacidad_buffer == 0) return 1;
            engine = new PipelineEngine(capacidad_buffer);
            return 0;
        } else return 2;
    } catch (const std::system_error&) { return 3; }
}

int pipeline_start(int n_alfa, int cant_alfa_por_hebra,
                   int n_beta, int cant_beta_por_hebra,
                   int m_gamma, int tiempo_gamma) {
    try {
        if (engine != NULL) {
            int result = engine->start(n_alfa, cant_alfa_por_hebra, 
                                    n_beta, cant_beta_por_hebra, 
                                    m_gamma, tiempo_gamma);                         
            return result;
        } else return 5;
    } catch (...) { return 6; }
}

int pipeline_wait_and_destroy(void) {
    try {
        if (engine != NULL) {
            engine->waitAndJoin();
            bool result = engine->completed();
            delete engine;
            engine = NULL;
            return result ? 0 : 2;
        } else return 1;
    } catch (const std::system_error&) { return 3; }
}

