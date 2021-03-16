#include "FfPt.h"
#include "SetXML.h"
#include "SetFile.h"
#include "TMath.h"

FfPt::FfPt(){
    std::cout << "-@-Creating FfPt"<<std::endl;
}

FfPt::~FfPt(){
    std::cout << "-$-Deleting FfPt"<<std::endl;
}

std::string FfPt::ObservableName(){
    return "FfPt";
}

void FfPt::SetObservable(fastjet::PseudoJet jet,
                             std::vector<std::shared_ptr<Particle>> particle_list,
                             std::vector<std::array<int, 2>> i_j ){
    
    
    for( auto& p : particle_list ){
        std::vector<std::array<int, 2>> i_h;
        if( HadTrigger(p, i_h) ){
            
            
            double delta_eta = p->eta() - jet.eta() ;
            double delta_phi = jet.delta_phi_to( p->GetPseudoJet() );
            double delta_r = TMath::Sqrt( delta_eta*delta_eta + delta_phi*delta_phi);
            
            if( delta_r <= jetR ){
                double pt = p->perp();
                double n = sub_ptr->nSubtraction(p);
                for( auto ij: i_j){
                    for( auto ih: i_h){
                        GetHist(ij[0],ij[1],ih[0],ih[1])->Fill( pt, n );
                    }
                }
            }
            
        }
    }

}
