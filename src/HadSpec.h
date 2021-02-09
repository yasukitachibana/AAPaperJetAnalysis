#ifndef HADSPEC_H_
#define HADSPEC_H_
#include "AnalyzeBase.h"
#include "SubtractionBase.h"

#include <iostream>

class HadSpec: public AnalyzeBase {
public:
    HadSpec();
    ~HadSpec();
    
private:
    std::string ObservableName();
    void OneEventAnalysis(std::vector<std::shared_ptr<Particle>> particle_list);
};

#endif 
