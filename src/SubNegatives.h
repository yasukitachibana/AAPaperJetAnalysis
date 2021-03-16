#ifndef SubNegatives_H_
#define SubNegatives_H_
#include "SubtractionBase.h"



class SubNegatives: public SubtractionBase {
public:
    SubNegatives();
    ~SubNegatives();
    
    std::vector <fastjet::PseudoJet>
    JetSubtraction(double jetR, std::vector <fastjet::PseudoJet> jets,
                   std::vector<std::shared_ptr<Particle>> particle_list );
    
    double ptSubtraction( std::shared_ptr<Particle> particle );
    double nSubtraction( std::shared_ptr<Particle> particle );
    
private:
    
    
};

#endif 
