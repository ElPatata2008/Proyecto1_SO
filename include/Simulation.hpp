#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <unistd.h>

static void SimulateWorkload(int time) { 
    // Multiplica el tiempo de espera en 10000, ya que
    // usleep() toma nanosegundos, por lo que habría que
    // Multiplicar por 1000 para tener 1 milisegundo, pero
    // como cada ud equivale a 10ms, se añade un 0 extra.
    usleep(time * 10000); 
}

#endif