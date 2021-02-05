#include "CombineJetShape.h"

CombineJetShape::CombineJetShape(){
    std::cout << "-@-Creating CombineJetShape"<<std::endl;
}


CombineJetShape::~CombineJetShape(){
    std::cout << "-$-Deleting CombineJetShape"<<std::endl;
}

void CombineJetShape::GetTotalHist(std::string total_hist_name){
    
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
        total_hist.Print("jetshape_");
        total_hist.Normalize("width");
        total_hist.Print("normalized_jetshape_");

    }else{
        std::cout << std::endl;
        std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
        std::cout << "[CombineJetShape] 0-total Jet" << std::endl;
        std::cout << "[CombineJetShape] Exit. "<< std::endl;
        std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
        std::cout << std::endl;
        exit(-1);
    }
    
    total_hist.DeleteTH1D();
    
}
