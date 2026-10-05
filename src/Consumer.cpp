#include "../include/Consumer.hpp"
#include "../include/Simulation.hpp"
#include <iostream>

Consumer::Consumer(int amount, int time, SharedBuffer& buffer): 
_dispatch(amount), _gammaTime(time), _buffer(buffer) { }

void Consumer::run() {
    for (int i = 0; i < _dispatch; i++) {                   // Repite por la cantidad total de paquetes.
        auto r = _buffer.pop();                             // pop() Ya se encarga de esperar.
        if (r.underflow) { SimulateWorkload(timePenalty); } // Si hubo underflow, tiempo de penalzación.

        std::cout << r.pkg.type << " "                      // Tipo del paquete.
                  << r.pkg.id   << " "                      // Id del paquete.
                  << r.remain   << "\n";                    // Paquetes restantes.
                
        SimulateWorkload(_gammaTime);                       // Tiempo de descanso por paquete.
    }
}

void* Consumer::enter(void* arg) {
    Consumer* self = static_cast<Consumer*>(arg);
    self->run();
    return nullptr;
}
