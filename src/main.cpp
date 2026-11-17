#include "../include/SharedBuffer.hpp"
#include "../include/Producer.hpp"
#include "../include/Package.hpp"
#include "../include/Consumer.hpp"
#include <iostream>
#include <fstream>
#include <string>

struct WorkloadResult {
    int qCap; 
    int nGamma; int timeGamma;
    int nAlpha; int capAlpha;
    int nBeta;  int capBeta;
};

WorkloadResult readWorkload(const std::string& file) {
    
    std::ifstream File(file);
    
    if (!File.is_open()) {
        std::cout << "\nNo se encontró el Workload.\n";
        std::cout << "\nRevise si el nombre es correcto o si la extensión es '.work'.\n";
        return WorkloadResult{0, 0, 0, 0, 0, 0, 0};
    }

    int qCap = 0; File >> qCap;
    int nGamma = 0; File >> nGamma;
    int timeGamma = 0; File >> timeGamma;
    int nAlpha = 0; File >> nAlpha;
    int capAlpha = 0; File >> capAlpha;
    int nBeta = 0; File >> nBeta;
    int capBeta = 0; File >> capBeta;

    return WorkloadResult{qCap, nGamma, timeGamma, nAlpha, capAlpha, nBeta, capBeta};
}

int main(int argc, char* argv[]) {

    if (argc == 1)      { std::cout << "\nFalta Ingresar Workload.\n";         return 1; }
    else if (argc >= 3) { std::cout << "\nDemasiados Workloads ingresados.\n"; return 1; }

    std::string file = argv[1];
    WorkloadResult wlr = readWorkload("test/" + file);

    if (wlr.qCap == 0 || 
        wlr.nGamma == 0 || 
        wlr.nAlpha == 0 || wlr.capAlpha == 0 || 
        wlr.nBeta == 0 || wlr.capBeta == 0
    ) { return 1; }

    

    return 0;
}