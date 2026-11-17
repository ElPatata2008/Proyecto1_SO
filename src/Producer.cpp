#include "../include/Producer.hpp"
#include "../include/Simulation.hpp"
#include "../include/alpha_kernels.hpp"

Producer::Producer(char type, int id, SharedBuffer& buffer, int amount): 
_type(type), _id(id), _buffer(buffer), _pkgAmount(amount) {

}

void Producer::run() {
    for (int i = 0; i < _pkgAmount; i++) {
        // SimulateWorkload(_times[i]);      

        computeOne();

        _buffer.push(_type); 

        counter++;                          
        if (counter == maxProcess && _pkgAmount > 0) {        
            SimulateWorkload(sleepTime);    
            counter = 0;                    
        }
    }
}   

void* Producer::enter(void* arg) {
    Producer* self = static_cast<Producer*>(arg);
    self->run();
    return nullptr;
}


Alpha::Alpha(int id, SharedBuffer& buffer, int amount): Producer('A', id, buffer, amount) { }

void Alpha::computeOne() { 
    data = std::vector<float>(nVertices, 0.0f);
    transformMesh(data, nVertices); 
} 

Beta::Beta(int id, SharedBuffer& buffer, int amount): Producer('B', id, buffer, amount) { }

void Beta::computeOne() {

}

