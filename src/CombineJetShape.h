#ifndef COMBINEJETSHAPE_H_
#define COMBINEJETSHAPE_H_

#include "CombineBase.h"
#include <iostream>

class CombineJetShape: public CombineBase{
public:
    CombineJetShape();
    ~CombineJetShape();
    
private:
    
    void GetTotalHist(std::string total_hist_name);

};

#endif 
