#ifndef COMBINEJETSHAPESUB_H_
#define COMBINEJETSHAPESUB_H_

#include "CombineBase.h"
#include <iostream>

class CombineJetShapeSub: public CombineBase{
public:
  CombineJetShapeSub();
  ~CombineJetShapeSub();
private:
  void InitExt();
  std::shared_ptr<Histogram> CreateHist( std::string hist_name );
  void GetTotalHist(std::string total_hist_name, double delta_rapidity);
  
  std::vector<double> sidebandRap;
  
};

#endif 
