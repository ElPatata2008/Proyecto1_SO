#include "../include/pipeline_api.h"
#include "../include/PipelineEngine.hpp"

static PipelineEngine* engine = NULL;

int pipeline_init(size_t capacidad_buffer) {
    if (engine == NULL) {
        engine = new PipelineEngine(capacidad_buffer);
    }
    return 0;
}

int pipeline_start(int n_alfa, int cant_alfa_por_hebra,
                   int n_beta, int cant_beta_por_hebra,
                   int m_gamma, int tiempo_gamma) {
    if (engine != NULL) {
        engine->start(n_alfa, cant_alfa_por_hebra, 
                      n_beta, cant_beta_por_hebra, 
                      m_gamma, tiempo_gamma);
    } else return 1;
    return 0;
}

int pipeline_wait_and_destroy(void) {
    if (engine != NULL) {
        engine->waitAndJoin();
        delete engine;
        engine = NULL;
    } else return 1;
    return 0;
}

