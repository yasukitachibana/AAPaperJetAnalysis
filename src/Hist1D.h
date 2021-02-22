#ifndef HIST1D_H_
#define HIST1D_H_

#include "Histogram.h"
#include "TH1.h"

class Hist1D: public Histogram {
public:
  using Histogram::Histogram;
  ~Hist1D();

  void Fill( double x );
  void Fill( double x, double val);
  void Print(std::string name = "", bool addHistname = true);
  void LoadHistFromFile();
  
  void Scale(double factor, std::string width = "");
  void Normalize(std::string width  = "");
  
  void Add(std::shared_ptr<Histogram> h);
  void Add(std::shared_ptr<Histogram> h, double factor);
  void Add(std::shared_ptr<Hist1D> h);
  void Add(std::shared_ptr<Hist1D> h, double factor);
  
  void SetErrors(Hist1D h_err2);

  TH1D* GetTH1D(){return Hist;}
  
  void DeleteTH(){
    delete[] binEdges;
    delete Hist;
  }
  
private:
  
  TH1D* Hist;
  int nBin;
  double* binEdges;

  void InitHist();
  void DivideWithError( double norm, double norm_error );
  void Add(TH1D *h);
  void Add(TH1D *h, double factor);

};

#endif 
