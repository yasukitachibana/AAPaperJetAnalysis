#include "JetShape.h"
#include "SetXML.h"
#include "SetFile.h"
#include "TMath.h"

JetShape::JetShape(){
  std::cout << "-@-Creating JetShape"<<std::endl;
}

JetShape::~JetShape(){
  std::cout << "-$-Deleting JetShape"<<std::endl;
}

std::string JetShape::ObservableName(){
  return "JetShape";
}

void JetShape::SetObservable(fjcore::PseudoJet jet,
                             std::vector<std::shared_ptr<Particle>> particle_list,
                             std::vector<std::array<int, 2>> i_j ){
  
  
  for( auto& p : particle_list ){
    std::vector<std::array<int, 2>> i_h;
    if( HadTrigger(p, i_h) ){
      
      double pt = sub_ptr->ptSubtraction(p);
      
      double delta_eta = p->eta() - jet.eta() ;
      double delta_phi = jet.delta_phi_to( p->GetPseudoJet() );
      double delta_r = TMath::Sqrt( delta_eta*delta_eta + delta_phi*delta_phi);
      
      for( auto ij: i_j){
        for( auto ih: i_h){
          
          GetHist(ij[0],ij[1],ih[0],ih[1])->Fill(delta_r, pt);
          
        }
      }
      
    }
  }
  
}
