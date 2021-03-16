#ifndef FFZ_H_
#define FFZ_H_
#include "AnalyzeBase.h"
#include "SubtractionBase.h"

#include <iostream>

class FfZ: public AnalyzeBase {
public:
    FfZ();
    ~FfZ();
    
private:
    std::string ObservableName();
    void SetObservable(fastjet::PseudoJet jet, std::vector<std::shared_ptr<Particle>> particle_list, std::vector<std::array<int, 2>> i_j );


};

#endif 
