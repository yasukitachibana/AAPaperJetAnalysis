#include "CombineBase.h"
#include "SetXML.h"
#include "SetFile.h"
#include "LoadFileBase.h"
#include "LoadJetScapeAscii.h"


CombineBase::~CombineBase(){
    std::cout << "-$-Deleting CombineBase"<<std::endl;
}

void CombineBase::Init(){
    std::cout << "[CombineBase] Intialize CombineBase"<<std::endl;
    
    jetRapMin = SetXML::Instance()->GetElementVectorDouble({"jetRapMin","Item"});
    jetRapMax = SetXML::Instance()->GetElementVectorDouble({"jetRapMax","Item"});
    jetPtMin = SetXML::Instance()->GetElementVectorDouble({"jetPtMin","Item"});
    jetPtMax = SetXML::Instance()->GetElementVectorDouble({"jetPtMax","Item"});
    
    hadRapMin = SetXML::Instance()->GetElementVectorDouble({"hadronRapMin","Item"});
    hadRapMax = SetXML::Instance()->GetElementVectorDouble({"hadronRapMax","Item"});
    hadPtMin = SetXML::Instance()->GetElementVectorDouble({"hadronPtMin","Item"});
    hadPtMax = SetXML::Instance()->GetElementVectorDouble({"hadronPtMax","Item"});
    
    
    inputStyle = SetXML::Instance()->GetElementText({"inputStyle"});
    
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ptHat = SetXML::Instance()->GetElementVectorDouble({"ptHat","Item"});
    nPtHatBin = ptHat.size()-1;
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    
}



void CombineBase::Combine(){
    
    for( int i_jet_pt = 0; i_jet_pt < jetPtMin.size(); i_jet_pt++ ){
        for( int i_jet_rap = 0; i_jet_rap < jetRapMin.size(); i_jet_rap++ ){
            for( int i_had_pt = 0; i_had_pt < hadPtMin.size(); i_had_pt++ ){
                for( int i_had_rap = 0; i_had_rap < hadRapMin.size(); i_had_rap++ ){
                    
                    std::cout <<  "=========================================================" << std::endl;
                    std::cout << "[CombineBase] jet pt: " << jetPtMin[i_jet_pt] << "-" << jetPtMax[i_jet_pt] << " GeV" << std::endl;
                    std::cout << "[CombineBase] jet rapidity: " << jetRapMin[i_jet_rap] << "-" << jetRapMax[i_jet_rap] << std::endl;
                    std::cout << "[CombineBase] particle pt: " << hadPtMin[i_had_pt] << "-" << hadPtMax[i_had_pt] << " GeV" << std::endl;
                    std::cout << "[CombineBase] particle rapidity " << hadRapMin[i_had_rap] << hadRapMax[i_had_rap] << std::endl;
                    std::cout <<  "---" << std::endl;
                    
                    
                    LoadHist(jetPtMin[i_jet_pt], jetPtMax[i_jet_pt],
                             jetRapMin[i_jet_rap], jetRapMax[i_jet_rap],
                             hadPtMin[i_had_pt], hadPtMax[i_had_pt],
                             hadRapMin[i_had_rap], hadRapMax[i_had_rap]);
                    
                    
                    CombineHist(jetPtMin[i_jet_pt], jetPtMax[i_jet_pt],
                                 jetRapMin[i_jet_rap], jetRapMax[i_jet_rap],
                                 hadPtMin[i_had_pt], hadPtMax[i_had_pt],
                                 hadRapMin[i_had_rap], hadRapMax[i_had_rap]);
                    
                    DeleteHist();
                }
            }
        }
    }
    //std::cout <<  "=========================================================" << std::endl;
}


void CombineBase::DeleteHist(){
    for( auto hist: hist_list ){
        hist->DeleteTH();
    }
    hist_list.clear();
    hist_list.shrink_to_fit();
}

void CombineBase::CombineHist( double jpmin, double jpmax,
                           double jrmin, double jrmax,
                           double hpmin, double hpmax,
                           double hrmin, double hrmax){

    std::string hist_name =
    SetFile::Instance()->GetHistName(jpmin,  jpmax,
                                     jrmin, jrmax,
                                     hpmin,  hpmax,
                                     hrmin, hrmax);
    
    double delta_rapidity = GetDeltaRapidity(jrmin, jrmax,
                                      hrmin, hrmax);
    GetTotalHist(hist_name, delta_rapidity);

}



void CombineBase::LoadHist( double jpmin, double jpmax,
                           double jrmin, double jrmax,
                           double hpmin, double hpmax,
                           double hrmin, double hrmax){
    
    for(int i_pthat_bin = 0; i_pthat_bin < nPtHatBin; i_pthat_bin++ ){
        
        
        std::string hist_name =
        SetFile::Instance()->GetHistName(ptHat[i_pthat_bin], ptHat[i_pthat_bin+1],
                                         jpmin,  jpmax,
                                         jrmin, jrmax,
                                         hpmin,  hpmax,
                                         hrmin, hrmax);
        
        std::cout << "[CombineBase] Load Histogram: " << hist_name << std::endl;
        auto hist_this_bin = std::make_shared<Hist1D>(hist_name);
        hist_this_bin->Init();
        hist_this_bin->LoadHistFromFile();
        
        
        
        //*******************************************************************************************
        //*******************************************************************************************
        std::unique_ptr<LoadFileBase> load_file_ptr;
        if(inputStyle == "JetScapeAscii" || inputStyle == "JetscapeAscii" ){
            load_file_ptr = std::unique_ptr<LoadJetScapeAscii> (new LoadJetScapeAscii());
        }else{
            std::cout << std::endl;
            std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
            std::cout << "[CombineBase] Input format, " << inputStyle << ", is not supported." << std::endl;
            std::cout << "[CombineBase] Exit. "<< std::endl;
            std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
            std::cout << std::endl;
            exit(-1);
        }
        //*******************************************************************************************
        double sigma, sigma_err;
        
        std::string sigma_file_name =  SetFile::Instance()->GetSigmaFileName(ptHat[i_pthat_bin], ptHat[i_pthat_bin+1]);
        std::cout << "[CombineBase] Load Sigma File: " << sigma_file_name << std::endl;
        load_file_ptr->LoadSigma(sigma_file_name, sigma, sigma_err);
        std::cout << "[CombineBase] Sigma = " << sigma << ", sigma error = " << sigma_err << std::endl;
        //*******************************************************************************************
        //*******************************************************************************************
        
        hist_this_bin->SetSigma(sigma, sigma_err);
        
        hist_list.push_back(hist_this_bin);
        
    }
    
    
}
