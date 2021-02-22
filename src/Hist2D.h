#ifndef HIST2D_H_
#define HIST2D_H_

#include "Histogram.h"
#include "TH2.h"

class Hist2D: public Histogram {
public:
  using Histogram::Histogram;
  ~Hist2D();

  void Fill( double x, double y );
  void Fill( double x, double y, double val);
  void Print(std::string name = "", bool addHistname = true);
  void LoadHistFromFile();

  void Scale(double factor, std::string width = "");
//  void Normalize(std::string width  = "");
//
  void Add(std::shared_ptr<Histogram> h);
  void Add(std::shared_ptr<Histogram> h, double factor);

  void Add(std::shared_ptr<Hist2D> h);
  void Add(std::shared_ptr<Hist2D> h, double factor);

  void Add(Hist2D h);
  void Add(Hist2D h, double factor);

  //
  TH2D* GetTH2D(){return Hist;}
  
  void DeleteTH(){
    delete Hist;
  }
  
  
  int GetNbinsX(){ return Hist->GetNbinsX();}
  int GetNbinsY(){ return Hist->GetNbinsY();}
  
  
  double GetVal( int ix, int iy ){ return Hist->GetBinContent(ix+1,iy+1);}
  double GetErr(int ix, int iy ){ return Hist->GetBinError(ix+1,iy+1);}
  double GetX( int ix ){ return Hist->GetXaxis()->GetBinCenter(ix+1);}
  double GetY( int iy ){ return Hist->GetYaxis()->GetBinCenter(iy+1);}

  
  
  void SetSidebandHist(std::shared_ptr<Histogram> h, double min, double max);
  void SetSidebandHist(std::shared_ptr<Hist2D> h, double min, double max);
  void SetSidebandHist(Hist2D h, double min, double max);
  
private:

  TH2D* Hist;
  int nBinX;
  int nBinY;
  std::vector<double> boundX;
  std::vector<double> boundY;

  void InitHist();
  void DivideWithError( double norm, double norm_error );
  
  void SetSidebandHist(TH2D *h, double min, double max);
  
  void Add(TH2D *h);
  void Add(TH2D *h, double factor);

};

#endif 
