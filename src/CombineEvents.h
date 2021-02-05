#ifndef COMBINEEVENTS_H_
#define COMBINEEVENTS_H_

#include "CombineBase.h"
#include "SetXML.h"
#include <iostream>

class CombineEvents{
public:
    CombineEvents();
    ~CombineEvents();


    void Combine();
    
private:
    
    std::unique_ptr<CombineBase> combine_ptr;
    
//    int nPtHatBin;
//    std::vector<double> ptHat;
    std::string observable;

    void Init();

};

#endif 
