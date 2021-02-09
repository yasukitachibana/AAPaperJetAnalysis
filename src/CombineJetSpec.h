#ifndef COMBINEJETSPEC_H_
#define COMBINEJETSPEC_H_

#include "CombineBase.h"
#include <iostream>

class CombineJetSpec: public CombineBase{
public:
    CombineJetSpec();
    ~CombineJetSpec();
    
private:
    
    void GetTotalHist(std::string total_hist_name, double delta_rapidity);

};

#endif 
