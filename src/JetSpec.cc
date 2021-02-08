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

void JetSpec::SetObservable(fjcore::PseudoJet jet,
                            std::vector<std::shared_ptr<Particle>> particle_list,
                            std::vector<std::array<int, 2>> i_j ){
    
    GetHist(0,0,0,0)->Fill( jet.perp(), 1.0 );
    
}
