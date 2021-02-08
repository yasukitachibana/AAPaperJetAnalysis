#include "FfZ.h"
#include "SetXML.h"
#include "SetFile.h"
#include "TMath.h"

FfZ::FfZ(){
    std::cout << "-@-Creating FfZ"<<std::endl;
}

FfZ::~FfZ(){
    std::cout << "-$-Deleting FfZ"<<std::endl;
}

std::string FfZ::ObservableName(){
    return "FfZ";
}

void FfZ::SetObservable(fjcore::PseudoJet jet,
                             std::vector<std::shared_ptr<Particle>> particle_list,
                             std::vector<std::array<int, 2>> i_j ){
    
    
    for( auto& p : particle_list ){
        std::vector<std::array<int, 2>> i_h;
        if( HadTrigger(p, i_h) ){
            
            double delta_eta = p->eta() - jet.eta() ;
            double delta_phi = jet.delta_phi_to( p->GetPseudoJet() );
            double delta_r = TMath::Sqrt( delta_eta*delta_eta + delta_phi*delta_phi);
            
            if( delta_r <= jetR ){
                
                double jpt = jet.perp();
                double pt = p->perp();
                double n = sub_ptr->nSubtraction(p);
                double z = pt*cos(delta_r)/jpt;
                
                for( auto ij: i_j){
                    for( auto ih: i_h){
                        GetHist(ij[0],ij[1],ih[0],ih[1])->Fill( z, n );
                    }
                }
            }
            
        }
    }

}
