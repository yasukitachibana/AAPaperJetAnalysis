#ifndef COMBINEFFZ_H_
#define COMBINEFFZ_H_

#include "CombineBase.h"
#include <iostream>

class CombineFfZ: public CombineBase{
public:
    CombineFfZ();
    ~CombineFfZ();
    
private:
    
    void GetTotalHist(std::string total_hist_name);

};

#endif 
