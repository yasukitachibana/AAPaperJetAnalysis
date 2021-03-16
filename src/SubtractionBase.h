#ifndef SUBTRACTIONBASE_H_
#define SUBTRACTIONBASE_H_

#include "Particle.h"
#include <vector>
#include <iostream>


class SubtractionBase{
public:
    
    virtual ~SubtractionBase();
    
    virtual std::vector <fastjet::PseudoJet> JetSubtraction(double jetR, std::vector <fastjet::PseudoJet> jets,
                                                           std::vector<std::shared_ptr<Particle>> particle_list ){ return jets; }

    virtual double ptSubtraction( std::shared_ptr<Particle> particle ){ return  particle->perp(); }

    virtual double nSubtraction( std::shared_ptr<Particle> particle ){ return  1.0; }

    
protected:
    
    
    
private:
    
    
    
    
    
    
};

#endif 
