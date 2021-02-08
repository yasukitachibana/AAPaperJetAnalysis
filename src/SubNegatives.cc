#include "SubNegatives.h"
#include "SetXML.h"
#include "SetFile.h"


SubNegatives::SubNegatives(){
    std::cout << "-@-Creating SubNegatives"<<std::endl;
}

SubNegatives::~SubNegatives(){
    std::cout << "-$-Deleting SubNegatives"<<std::endl;
}

std::vector <fjcore::PseudoJet>
SubNegatives::JetSubtraction(double jetR, std::vector <fjcore::PseudoJet> jets_in,
               std::vector<std::shared_ptr<Particle>> particle_list )
{
    std::vector <fjcore::PseudoJet> jets_out;
    
    for( auto& j : jets_in ){
        
        double e_j = j.e();
        double px_j = j.px();
        double py_j = j.py();
        double pz_j = j.pz();
        
        for( auto& p : particle_list ){
            if( p->GetStat() == -1 && j.delta_R(p->GetPseudoJet()) <= jetR ){
                e_j -= p->e();
                px_j -= p->px();
                py_j -= p->py();
                pz_j -= p->pz();
            }
        }

        j.reset( px_j, py_j, pz_j, e_j );

        jets_out.push_back(j);
        
    }
    return jets_out;
}


double SubNegatives::ptSubtraction( std::shared_ptr<Particle> particle ){
    
    if( particle->GetStat() != -1 ){
        return particle->perp();
    }else{
        return -1.0 * particle->perp();
    }
    
}

double SubNegatives::nSubtraction( std::shared_ptr<Particle> particle ){
    
    if( particle->GetStat() != -1 ){
        return 1.0;
    }else{
        return -1.0;
    }
    
}
