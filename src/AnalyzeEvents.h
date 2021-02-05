#ifndef ANALYZEEVENTS_H_
#define ANALYZEEVENTS_H_

#include "AnalyzeBase.h"
#include "JetShape.h"
#include <iostream>
#include <vector>

class AnalyzeEvents{
public:
    AnalyzeEvents();
    ~AnalyzeEvents();

    void Init();
    void Analyze();
    
private:
      
    std::unique_ptr<AnalyzeBase> analyze_ptr;
    
    int nPtHatBin;
    std::vector<double> ptHat;
    std::string observable;

};

#endif 
