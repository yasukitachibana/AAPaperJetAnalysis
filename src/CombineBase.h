#ifndef COMBINEBASE_H_
#define COMBINEBASE_H_


#include "Histogram.h"
#include <iostream>
#include <vector>

class CombineBase{
public:
    
    virtual ~CombineBase();
    
    void Init();
    void Combine();
    
protected:
    
    std::vector<std::shared_ptr<Histogram>> hist_list;
    
private:
    
    void LoadHist( double jpmin, double jpmax,
                  double jrmin, double jrmax,
                  double hpmin, double hpmax,
                  double hrmin, double hrmax);
    
    void CombineHist( double jpmin, double jpmax,
                  double jrmin, double jrmax,
                  double hpmin, double hpmax,
                  double hrmin, double hrmax);
    
    virtual double GetDeltaRapidity(double jrmin, double jrmax, double hrmin, double hrmax){ return 2.0*(jrmax-jrmin); }
    virtual void GetTotalHist(std::string total_hist_name, double delta_rapidity){}
    
    void DeleteHist();
    
    int nPtHatBin;
    std::vector<double> ptHat;
    
    std::vector<double> jetRapMin;
    std::vector<double> jetRapMax;
    std::vector<double> jetPtMin;
    std::vector<double> jetPtMax;
    
    std::vector<double> hadRapMin;
    std::vector<double> hadRapMax;
    std::vector<double> hadPtMin;
    std::vector<double> hadPtMax;
    
    std::string inputStyle;
    
};

#endif 
