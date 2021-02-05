#ifndef LOADFILEBASE_H_
#define LOADFILEBASE_H_

#include "Particle.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <float.h>
#include <math.h>



class LoadFileBase{
public:
    
    virtual ~LoadFileBase();
    
    virtual void Load(std::string input_filename){}
    virtual void GetParticleList(){}
    virtual int GetLine(){return 0;}
    virtual void ShowLine(){}
    virtual int EventEnd(){return 0;}
    virtual int ValidLine(){return 0;}
    virtual int Last(){return 1;}
    virtual void LoadSigma(std::string sigma_filename, double &sigma, double &sigma_err){}
    
    virtual std::shared_ptr<Particle> GetParticle(){return nullptr;}

protected:
    

    
private:

    
    
    
    
    
};

#endif 
