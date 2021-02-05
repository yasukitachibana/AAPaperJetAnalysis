#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <float.h>
#include <math.h>
#include <vector>
#include <iomanip>
#include "TH1.h"
//#include "Particle.h"




class Histogram{
public:
    Histogram(std::string histname);
    ~Histogram();
    
    void Init();
    
    void LoadHistFromFile();
    void SetSigma(double sigma, double sigma_err);
    double GetNjetSigmaOverEev();
    
    void Fill( double x, double y);
    
    void Print();
    void Print(std::string name, bool addHistname = true);
    
    void Scale(double factor, std::string width = "");
    void Normalize(std::string width  = "");
            
    void Add(TH1D *h);
    void Add(TH1D *h, double factor);
    void Add(std::shared_ptr<Histogram> h);
    void Add(std::shared_ptr<Histogram> h, double factor);
    
    std::string HistName();
    
    //+++++++++++++++++++++++++++++++++++++
    double Nev(){return nEv;}
    void EventCount(int n){nEv+=double(n);}
    void EventCount(double n){nEv+=n;}
    void EventCount(){nEv+=1.0;}
    void ResetNev(double n_total){nEv=n_total;}
    void ResetNev(int n_total){nEv=double(n_total);}
    //+++++++++++++++++++++++++++++++++++++
    double Njet(){return nJet;}
    void JetTriggered(int n){nJet+=double(n);}
    void JetTriggered(double n){nJet+=n;}
    void JetTriggered(){nJet+=1.0;}
    void ResetNjet(double n_total){nJet=n_total;}
    void ResetNjet(int n_total){nJet=double(n_total);}
    //+++++++++++++++++++++++++++++++++++++
    double Sigma(){return sigma;}
    double SigmaErr(){return sigma_err;}
    //+++++++++++++++++++++++++++++++++++++
    
    
    void DeleteTH1D(){
        delete[] binEdges;
        delete Hist;
    }
    


//    void SetSigma(double sigma_in, double sigma_error_in);
//    void Out(std::string label, std::string out_dir);
//    void CheckPrintHist();
//
//
//    double sigma;
//    double sigma_error;
//    double N_jet;
//    double N_ev;
//


    
private:
    
    TH1D* GetTH1D(){return Hist;}
    void DivideWithError( double norm, double norm_error );
    
    std::string histname;
    TH1D* Hist;
    double nJet;
    double nEv;

    int nBin;
    double* binEdges;

    double sigma;
    double sigma_err;
//    int Nbin;
//    double* rBin_edges;
//    int pTHatMin;
//    int pTHatMax;


//    void Initialization( std::vector<double> rBins );
//    void Normalize();

//
    


};

#endif 
