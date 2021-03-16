#include "JetSpec.h"
#include "SetXML.h"
#include "SetFile.h"
#include "TMath.h"

JetSpec::JetSpec(){
    std::cout << "-@-Creating JetSpec"<<std::endl;
}

JetSpec::~JetSpec(){
    std::cout << "-$-Deleting JetSpec"<<std::endl;
}

std::string JetSpec::ObservableName(){
    return "JetSpec";
}

void JetSpec::SetObservable(fastjet::PseudoJet jet,
                            std::vector<std::shared_ptr<Particle>> particle_list,
                            std::vector<std::array<int, 2>> i_j ){
    for( auto ij: i_j){
        for( int i_had_pt = 0; i_had_pt < hadPtMin.size(); i_had_pt++ ){
            for( int i_had_rap = 0; i_had_rap < hadRapMin.size(); i_had_rap++ ){
                
                GetHist(ij[0],ij[1],i_had_pt,i_had_rap)->Fill( jet.perp(), 1.0 );
                
            }
        }
    }
    
}
