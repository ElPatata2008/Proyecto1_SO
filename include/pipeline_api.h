#ifndef PIPELINE_API_H
#define PIPELINE_API_H

#include <stddef.h>

#ifdef __cplusplus

extern "C" {
    int pipeline_init(size_t capacidad_buffer);
    int pipeline_start(int n_alfa, int cant_alfa_por_hebra,
                       int n_beta, int cant_beta_por_hebra,
                       int m_gamma, int tiempo_gamma);
    int pipeline_wait_and_destroy(void);
}
#endif

#endif