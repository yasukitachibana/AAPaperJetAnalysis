#include "CombineFfZ.h"

CombineFfZ::CombineFfZ(){
    std::cout << "-@-Creating CombineFfZ"<<std::endl;
}


CombineFfZ::~CombineFfZ(){
    std::cout << "-$-Deleting CombineFfZ"<<std::endl;
}

void CombineFfZ::GetTotalHist(std::string total_hist_name, double delta_rapidity){
    
    Hist1D total_hist(total_hist_name);
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
    if(nJetTotal!=0){
        total_hist.Scale(1.0/nJetTotal,"width");
        total_hist.Print("ffz_");
    }else{
        std::cout << "[CombineFfZ] 0-total Jet" << std::endl;
        std::cout << "[CombineFfZ] Skip. "<< std::endl;
    }
    
    total_hist.DeleteTH();
    
}
