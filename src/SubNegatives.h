#ifndef SubNegatives_H_
#define SubNegatives_H_
#include "SubtractionBase.h"



class SubNegatives: public SubtractionBase {
public:
    SubNegatives();
    ~SubNegatives();
    
    std::vector <fjcore::PseudoJet>
    JetSubtraction(double jetR, std::vector <fjcore::PseudoJet> jets,
                   std::vector<std::shared_ptr<Particle>> particle_list );
    
    double ptSubtraction( std::shared_ptr<Particle> particle );
    
private:
    
    
};

#endif 
