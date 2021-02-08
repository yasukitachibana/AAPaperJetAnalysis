#include "CombineFfPt.h"

CombineFfPt::CombineFfPt(){
    std::cout << "-@-Creating CombineFfPt"<<std::endl;
}


CombineFfPt::~CombineFfPt(){
    std::cout << "-$-Deleting CombineFfPt"<<std::endl;
}

void CombineFfPt::GetTotalHist(std::string total_hist_name){
    
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
    if(nJetTotal!=0){
        total_hist.Scale(1.0/nJetTotal,"width");
        total_hist.Print("ffpt_");
    }else{
        std::cout << "[CombineFfPt] 0-total Jet" << std::endl;
        std::cout << "[CombineFfPt] Skip. "<< std::endl;
    }
    
    total_hist.DeleteTH1D();
    
}
