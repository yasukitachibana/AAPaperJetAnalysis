#ifndef CombineHadSpec_H_
#define CombineHadSpec_H_

#include "CombineBase.h"
#include <iostream>

class CombineHadSpec: public CombineBase{
public:
    CombineHadSpec();
    ~CombineHadSpec();
    
private:
    
    void GetTotalHist(std::string total_hist_name, double delta_rapidity);
    double GetDeltaRapidity(double jrmin, double jrmax, double hrmin, double hrmax){ return 2.0*(hrmax-hrmin); }


};

#endif 
