#include "../include/SharedBuffer.hpp"
#include "../include/Producer.hpp"
#include "../include/Package.hpp"
#include "../include/Consumer.hpp"
#include <iostream>
#include <fstream>
#include <string>

struct WorkloadResult {
    int qCap;
    int gTime;
    int Aamount;
    std::vector<int> Atimes;
    int Bamount;
    std::vector<int> Btimes;
};

WorkloadResult readWorkload(const std::string& file) {
    
    std::ifstream File(file);
    
    if (!File.is_open()) {
        std::cout << "\nNo se encontró el Workload.\n";
        std::cout << "\nSólo hace falta ingresar el nombre del Workload."
                  << "\nEl programa se encarga de buscarlo y añadir .work .\n";
        return WorkloadResult{0, 0, 0, {}, 0, {}};
    }

    int qCap = 0; File >> qCap;
    int gTime = 0; File >> gTime;

    int Aa = 0; File >> Aa;
    std::vector<int> At;
    for (int i = 0; i < Aa; i++) {
        int atime = 0;
        File >> atime;
        At.push_back(atime);
    }

    int Ba = 0; File >> Ba;
    std::vector<int> Bt;
    for (int i = 0; i < Ba; i++) {
        int btime = 0;
        File >> btime;
        Bt.push_back(btime);
    }

    return WorkloadResult{qCap, gTime, Aa, At, Ba, Bt};
}

int main(int argc, char* argv[]) {

    if (argc == 1)      { std::cout << "\nFalta Ingresar Workload.\n";         return 1; }
    else if (argc >= 3) { std::cout << "\nDemasiados Workloads ingresados.\n"; return 1; }

    std::string file = argv[1];
    WorkloadResult wlr = readWorkload("test/" + file + ".work");

    if (wlr.qCap == 0 && wlr.gTime == 0 &&
        wlr.Aamount == 0 && wlr.Atimes.size() == 0 && 
        wlr.Bamount == 0 && wlr.Btimes.size() == 0
    ) { return 1; }

    // std::cout << "\nQueue Capacity: " << wlr.qCap
    //           << "\nGamma Time:     " << wlr.gTime
    //           << "\nAlpha Amount:   " << wlr.Aamount
    //           << "\nAlpha Times:    ";
    //           for (int i = 0; i < wlr.Aamount; i++) { std::cout << wlr.Atimes[i] << " "; }
    // std::cout << "\nBeta Amount:    " << wlr.Bamount
    //           << "\nBeta Times:     ";
    //           for (int i = 0; i < wlr.Bamount; i++) { std::cout << wlr.Btimes[i] << " "; }
    // std::cout << std::endl;

    SharedBuffer sb(wlr.qCap);
    Producer A('A', sb, wlr.Atimes);
    Producer B('B', sb, wlr.Btimes);
    Consumer G(wlr.Aamount + wlr.Bamount, wlr.gTime, sb);

    pthread_t At, Bt, Gt;

    pthread_create(&At, NULL, Producer::enter, &A);
    pthread_create(&Bt, NULL, Producer::enter, &B);
    pthread_create(&Gt, NULL, Consumer::enter, &G);

    pthread_join(At, NULL);
    pthread_join(Bt, NULL);
    pthread_join(Gt, NULL);

    std::cout << "\nSimulation Finilized Successfully: " << wlr.Aamount + wlr.Bamount << " packages dispachted.\n";
    return 0;
}