#ifndef COMBINEFFPT_H_
#define COMBINEFFPT_H_

#include "CombineBase.h"
#include <iostream>

class CombineFfPt: public CombineBase{
public:
    CombineFfPt();
    ~CombineFfPt();
    
private:
    
    void GetTotalHist(std::string total_hist_name);

};

#endif 
