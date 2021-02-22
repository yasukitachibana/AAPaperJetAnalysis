#ifndef JETSHAPESUB_H_
#define JETSHAPESUB_H_
#include "AnalyzeBase.h"
#include "SubtractionBase.h"

#include <iostream>

class JetShapeSub: public AnalyzeBase {
public:
  JetShapeSub();
  ~JetShapeSub();
  
private:
  std::string ObservableName();
  void GenerateHist(double ptHatMin, double ptHatMax);
  void SetObservable(fjcore::PseudoJet jet, std::vector<std::shared_ptr<Particle>> particle_list, std::vector<std::array<int, 2>> i_j );
    
    
  };
  
#endif 
