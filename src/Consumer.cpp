#include "../include/Consumer.hpp"
#include "../include/Simulation.hpp"
#include <iostream>
#include <string>

Consumer::Consumer(int id, int time, SharedBuffer& buffer): 
_id(id), _gammaTime(time), _buffer(buffer) { }

void Consumer::run() {
    while (true) {
        auto r = _buffer.pop();                             
        if (r.done) break;                                  
        if (r.underflow) { SimulateWorkload(timePenalty); } 

        std::string result = "G" + std::to_string(_id) 
                           + " " + r.pkg.type 
                           + " " + std::to_string(r.pkg.id) 
                           + " " + std::to_string(r.remain)
                           + "\n";

        std::cout << result;                 
                
        SimulateWorkload(_gammaTime);                       

    }
}

