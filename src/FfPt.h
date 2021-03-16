#ifndef FFPT_H_
#define FFPT_H_
#include "AnalyzeBase.h"
#include "SubtractionBase.h"

#include <iostream>

class FfPt: public AnalyzeBase {
public:
    FfPt();
    ~FfPt();
    
private:
    std::string ObservableName();
    void SetObservable(fastjet::PseudoJet jet, std::vector<std::shared_ptr<Particle>> particle_list, std::vector<std::array<int, 2>> i_j );


};

#endif 
