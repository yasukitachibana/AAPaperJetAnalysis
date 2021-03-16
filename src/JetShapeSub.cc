#include "JetShapeSub.h"
#include "SetXML.h"
#include "SetFile.h"
#include "TMath.h"
#include "Hist2D.h"

JetShapeSub::JetShapeSub(){
  std::cout << "-@-Creating JetShapeSub"<<std::endl;
}

JetShapeSub::~JetShapeSub(){
  std::cout << "-$-Deleting JetShapeSub"<<std::endl;
}

std::string JetShapeSub::ObservableName(){
  return "JetShapeSub";
}


void JetShapeSub::GenerateHist(double ptHatMin, double ptHatMax){
  
  int nHist = 0;
  
  for( int i_jet_pt = 0; i_jet_pt < jetPtMin.size(); i_jet_pt++ ){
    for( int i_jet_rap = 0; i_jet_rap < jetRapMin.size(); i_jet_rap++ ){
      for( int i_had_pt = 0; i_had_pt < hadPtMin.size(); i_had_pt++ ){
        for( int i_had_rap = 0; i_had_rap < hadRapMin.size(); i_had_rap++ ){
          
          std::string hist_name = GetHistName(ptHatMin, ptHatMax, i_jet_pt, i_jet_rap, i_had_pt, i_had_rap);
          std::cout << "[JetShapeSub] generate histogram #" << nHist << " " << hist_name << std::endl;
          
          auto hist_this_bin = std::make_shared<Hist2D>(hist_name);
          hist_list.push_back(hist_this_bin);
          
          nHist ++;
          std::cout << GetHist(i_jet_pt, i_jet_rap, i_had_pt, i_had_rap)->HistName() << std::endl;
          
        }//had_rap
      }//had_pt
    }//jet_rap
  }//jet_pt
  
  std::cout << "[JetShapeSub] number of generated histogram: " << nHist << std::endl;
  
}

void JetShapeSub::SetObservable(fastjet::PseudoJet jet,
                                std::vector<std::shared_ptr<Particle>> particle_list,
                                std::vector<std::array<int, 2>> i_j ){
  
  
  for( auto& p : particle_list ){
    std::vector<std::array<int, 2>> i_h;
    if( HadTrigger(p, i_h) ){
      
      double pt = sub_ptr->ptSubtraction(p);
      
      double delta_eta = p->eta() - jet.eta() ;
      double delta_phi = jet.delta_phi_to( p->GetPseudoJet() );
      
      for( auto ij: i_j){
        for( auto ih: i_h){
          
          GetHist(ij[0],ij[1],ih[0],ih[1])->Fill(delta_phi, delta_eta, pt);
          
        }
      }
      
    }
  }
  
}
