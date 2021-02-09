#include "HadSpec.h"
#include "SetXML.h"
#include "SetFile.h"
#include "TMath.h"

HadSpec::HadSpec(){
    std::cout << "-@-Creating HadSpec"<<std::endl;
}

HadSpec::~HadSpec(){
    std::cout << "-$-Deleting HadSpec"<<std::endl;
}

std::string HadSpec::ObservableName(){
    return "HadSpec";
}

void HadSpec::OneEventAnalysis(std::vector<std::shared_ptr<Particle>> particle_list){
    
    for( auto& p : particle_list ){
        for( int i_jet_pt = 0; i_jet_pt < jetPtMin.size(); i_jet_pt++ ){
            for( int i_jet_rap = 0; i_jet_rap < jetRapMin.size(); i_jet_rap++ ){
                
                std::vector<std::array<int, 2>> i_h;
                if( HadTrigger(p, i_h) ){
                    for( auto ih: i_h){
                        
                        double pt = sub_ptr->ptSubtraction(p);
                        GetHist(i_jet_pt,i_jet_rap,ih[0],ih[1])->Fill( pt, 1.0 );
                        
                    }
                }
                
            }
        }
    }
    
}
