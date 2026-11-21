#include "../include/Producer.hpp"
#include "../include/Simulation.hpp"
#include "../include/alpha_kernels.hpp"
#include <iostream>

Producer::Producer(char type, int id, SharedBuffer& buffer, int amount): 
_type(type), _id(id), _buffer(buffer), _pkgAmount(amount) {

}

void Producer::run() {
    for (int i = 0; i < _pkgAmount; i++) {
        if (!computeOne()) {
            std::cerr << "[ERROR] " << _type << _id;
            _buffer.shutdown();
            return;
        }
        _buffer.push(_type); 
        counter++;                          
        if (counter == maxProcess && _pkgAmount - (i + 1) > 0) {        
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

Producer::~Producer() { }

Alpha::Alpha(int id, SharedBuffer& buffer, int amount): Producer('A', id, buffer, amount) { 
    angle = radiansToDegree(id);
    data = std::vector<float>(3 * nVertices, 0.0f);
}

bool Alpha::computeOne() { 
    return transformMesh(data.data(), nVertices, angle); 
} 

Beta::Beta(int id, SharedBuffer& buffer, int amount): Producer('B', id, buffer, amount) { 
    data = std::vector<float>(n, 0.0f);
}

bool Beta::computeOne() {
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < n; i++) {
        data[i] = data[i] * 0.5f + 1.0f;
    }
    return true;
}

