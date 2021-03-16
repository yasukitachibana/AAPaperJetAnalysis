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
  void SetObservable(fastjet::PseudoJet jet, std::vector<std::shared_ptr<Particle>> particle_list, std::vector<std::array<int, 2>> i_j );
  
  
};

#endif 
