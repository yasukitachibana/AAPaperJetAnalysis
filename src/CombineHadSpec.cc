#include "CombineHadSpec.h"

CombineHadSpec::CombineHadSpec(){
    std::cout << "-@-Creating CombineHadSpec"<<std::endl;
}


CombineHadSpec::~CombineHadSpec(){
    std::cout << "-$-Deleting CombineHadSpec"<<std::endl;
}

void CombineHadSpec::GetTotalHist(std::string total_hist_name, double delta_rapidity){
    
    Histogram total_hist(total_hist_name);
    total_hist.Init();
    
    
    double nJetTotal = 0.0;
    
    for( auto hist: hist_list ){
        double n_ev = hist->Nev();
        if( n_ev != 0 ){
            nJetTotal += hist->GetNjetSigmaOverEev();
            double sigma = hist->Sigma();
            total_hist.Add(hist, sigma/n_ev );
        }
    }
    
    total_hist.Print("count_");
    
    total_hist.Scale(1.0,"width");
    total_hist.Print("hadspec_dNdpt_");
    std::cout << "[CombineHadSpec] delta_rapidity = " << delta_rapidity << std::endl;
    total_hist.Scale(1.0/delta_rapidity);
    total_hist.Print("hadspec_dNdptdrap_");
    
    total_hist.DeleteTH1D();
    
}
