#ifndef JETSHAPE_H_
#define JETSHAPE_H_
#include "AnalyzeBase.h"
#include "SubtractionBase.h"

#include <iostream>

class JetShape: public AnalyzeBase {
public:
    JetShape();
    ~JetShape();
    
private:
    std::string ObservableName();
    void SetObservable(fjcore::PseudoJet jet, std::vector<std::shared_ptr<Particle>> particle_list, std::vector<std::array<int, 2>> i_j );
//    const std::string input_file_name = "";
//    std::vector<std::shared_ptr<HistJetShape>> hist_list;
//
//    double jetR;
//    int chJet;
//    double primHadPtMin;
//    int jetRapidity;
//    std::vector<double> jetRapMin;
//    std::vector<double> jetRapMax;
//    std::vector<double> jetPtMin;
//    std::vector<double> jetPtMax;
//
//    int chHad;
//    int hadRapidity;
//    std::vector<double> hadRapMin;
//    std::vector<double> hadRapMax;
//    std::vector<double> hadPtMin;
//    std::vector<double> hadPtMax;
    


    


};

#endif 
