#include <iostream>
#include <fstream>
#include <string>
#include "../include/pipeline_api.h"

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
    WorkloadResult wlr = readWorkload(file);

    bool validAplha = wlr.capAlpha > 0 && wlr.nAlpha > 0;
    bool validBeta  = wlr.capBeta  > 0 && wlr.nBeta  > 0;

    if (wlr.qCap == 0 || 
        wlr.nGamma == 0 || 
        !validAplha || !validBeta ||
        wlr.nAlpha + wlr.nBeta == 0
    ) { 
        std::cerr << "Archivo no válido: \n"
                  << wlr.qCap << "\n"
                  << wlr.nGamma << " " << wlr.timeGamma << "\n"
                  << wlr.nAlpha << " " << wlr.capAlpha << "\n"
                  << wlr.nBeta << " " << wlr.capBeta << "\n";
        std::cerr << "Valid: \n"
                  << "Alpha: " << !validAplha << "\n"
                  << "Beta:  " << !validBeta << "\n";
        return 1; 
    }

    int init = 0, start = 0, wait_and_destroy = 0;

    init = pipeline_init(wlr.qCap);
    if (init == 0) start = pipeline_start(wlr.nAlpha, wlr.capAlpha, wlr.nBeta, wlr.capBeta, wlr.nGamma, wlr.timeGamma);
    if (init == 0) wait_and_destroy = pipeline_wait_and_destroy();

    if (init == 0 && start == 0 && wait_and_destroy == 0) {
        int total = wlr.nAlpha * wlr.capAlpha + wlr.nBeta * wlr.capBeta;
        std::cout << "\nSimulación heterogénea finalizada exitosamente: " 
                  << total << " paquetes despachados.\n";
        return 0;
    }
    else {
        std::cerr << "\nSimulación heterogénea finalizada con errores:\n";
        std::cerr << "\nPipeline Init: ";
        switch(init) {
            case 0: std::cerr << "[0] Pipeline inicializado correctamente."; break;
            case 1: std::cerr << "[1] Capacidad del buffer no puede ser cero."; break;
            case 2: std::cerr << "[2] Pipeline ya inicializado."; break;
            default: std::cerr << "[Error desconocido] Error inesperado."; break;
        }
        std::cerr << "\nPipeline Start: ";
        switch(start) {
            case 0: std::cerr << "[0] Pipeline iniciado correctamente."; break;
            case 1: std::cerr << "[1] Pipeline iniciado con anterioridad."; break;
            case 2: std::cerr << "[2] Parámetros inválidos para iniciar el Pipeline."; break;
            case 3: std::cerr << "[3] Error al crear un hilo productor."; break;
            case 4: std::cerr << "[4] Error al crear un hilo consumidor."; break;
            case 5: std::cerr << "[5] Pipeline no inicializado con anterioridad."; break;
            default: std::cerr << "[Error desconocido] Error inesperado."; break;
        }   
        std::cerr << "\nPipeline Wait and Destroy: ";
        switch(wait_and_destroy) {
            case 0: std::cerr << "[0] Pipeline destruido correctamente."; break;
            case 1: std::cerr << "[1] Pipeline destruido antes de esperar y destruir."; break;
            case 2: std::cerr << "[2] Pipeline terminó incompleto."; break;
            default: std::cerr << "[Error desconocido] Error inesperado."; break;
        }
        return 1;
    }
}