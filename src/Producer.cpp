#include "../include/Producer.hpp"
#include "../include/Simulation.hpp"

Producer::Producer(char type, SharedBuffer& buffer, const std::vector<int>& times): 
_type(type), _buffer(buffer), _times(times) {

}

void Producer::run() {
    for (int i = 0; i < _times.size(); i++) {
        SimulateWorkload(_times[i]);            // Simula carga de trabajo.

        _buffer.push(Package{_type, i + 1});    // Se empuja a la cola.

        if (_times.size() > maxProcess) {       // No va a descansar si la cantidad
            counter++;                          // paquetes es igual a 5.
            if (counter == maxProcess) {        // Si ya van 5 procesos,
                SimulateWorkload(sleepTime);    // Se va a descansar.
                counter = 0;                    // Reinicio del contador.
            }
        }
    }
}   

void* Producer::enter(void* arg) {
    Producer* self = static_cast<Producer*>(arg);
    self->run();
    return nullptr;
}
