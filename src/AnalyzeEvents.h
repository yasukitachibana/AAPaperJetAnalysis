#ifndef ANALYZEEVENTS_H_
#define ANALYZEEVENTS_H_


#include "AnalyzeBase.h"
#include "JetSpec.h"
#include "HadSpec.h"
#include "JetShape.h"
#include "JetShapeSub.h"
#include "FfPt.h"
#include "FfZ.h"
#include <iostream>
#include <vector>

class AnalyzeEvents{
public:
  AnalyzeEvents();
  ~AnalyzeEvents();
  
  void Init();
  void Analyze();
  
private:
  void CreateAnalyze( std::string observable );
  
  std::unique_ptr<AnalyzeBase> analyze_ptr;
  
  int nPtHatBin;
  std::vector<double> ptHat;
  std::string observable;
  
};

#endif 
