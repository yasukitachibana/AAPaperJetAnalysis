#include "CombineJetShapeSub.h"

CombineJetShapeSub::CombineJetShapeSub(){
  std::cout << "-@-Creating CombineJetShapeSub"<<std::endl;
}


CombineJetShapeSub::~CombineJetShapeSub(){
  std::cout << "-$-Deleting CombineJetShapeSub"<<std::endl;
}

std::shared_ptr<Histogram> CombineJetShapeSub::CreateHist( std::string hist_name ){
  std::cout << "[CombineJetShapeSub] Load 2D Histogram: " << hist_name << std::endl;
  return std::make_shared<Hist2D>(hist_name);
}

void CombineJetShapeSub::InitExt() {
  std::cout << "[CombineJetShapeSub] Get Additional Info"<< std::endl;
  
  sidebandRap = SetXML::Instance()->GetElementVectorDouble({"sidebandRap","Item"});
  
  std::cout << "[CombineJetShapeSub] Sideband Subtraction "<< sidebandRap[0] << "-" << sidebandRap[1] <<std::endl;
}

void CombineJetShapeSub::GetTotalHist(std::string total_hist_name, double delta_rapidity){
  
  std::cout << "[CombineJetShapeSub] Sideband Subtraction "<< total_hist_name <<std::endl;
  
  Hist2D total_hist("2d_"+total_hist_name);
  total_hist.Init();
  
  double nJetTotal = 0.0;
  
  for( auto hist: hist_list ){
    double n_ev = hist->Nev();
    if( n_ev != 0 ){
      nJetTotal += hist->GetNjetSigmaOverEev();
      double sigma = hist->Sigma();
      total_hist.Add(hist, sigma/n_ev);
    }
  }
  
  
  total_hist.Scale(1.0/nJetTotal);
  
  
  
  Hist2D sideband_hist("sideband_"+total_hist_name);
  sideband_hist.Init();
  
  sideband_hist.SetSidebandHist(total_hist,sidebandRap[0],sidebandRap[1]);
  
  total_hist.Print("count_before_sub_");
  sideband_hist.Print();
  
  total_hist.Add( sideband_hist, -1.0 );
  sideband_hist.DeleteTH();
  total_hist.Print("count_");
  
  
  Hist1D jetshape_hist(total_hist_name);
  jetshape_hist.Init();
  
  Hist1D jetshape_err2_hist("err2_"+total_hist_name);
  jetshape_err2_hist.Init();
  
  
  int n_phi = total_hist.GetNbinsX();
  int n_eta = total_hist.GetNbinsY();
  
  for(int i_phi=0; i_phi<n_phi; i_phi++){
    for(int i_eta=0; i_eta<n_eta; i_eta++){
      
      double delta_phi = total_hist.GetX(i_phi);
      double delta_eta = total_hist.GetY(i_eta);
      double val = total_hist.GetVal(i_phi,i_eta);
      double err = total_hist.GetErr(i_phi,i_eta);
      
      double delta_r = sqrt(delta_phi*delta_phi+delta_eta*delta_eta);
      
      jetshape_hist.Fill(delta_r, val);
      jetshape_err2_hist.Fill(delta_r, err*err);
      
    }
  }
  total_hist.DeleteTH();
  
  jetshape_hist.SetErrors(jetshape_err2_hist);
  jetshape_err2_hist.DeleteTH();
  
  
  jetshape_hist.Scale(1.0,"width");
  jetshape_hist.Print("jetshape_");
  jetshape_hist.Normalize("width");
  jetshape_hist.Print("normalized_jetshape_");

  
  jetshape_hist.DeleteTH();
  
}
