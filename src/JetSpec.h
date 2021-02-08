#ifndef JETSPEC_H_
#define JETSPEC_H_
#include "AnalyzeBase.h"
#include "SubtractionBase.h"

#include <iostream>

class JetSpec: public AnalyzeBase {
public:
    JetSpec();
    ~JetSpec();
    
private:
    std::string ObservableName();
    void SetObservable(fjcore::PseudoJet jet, std::vector<std::shared_ptr<Particle>> particle_list, std::vector<std::array<int, 2>> i_j );
};

#endif 
