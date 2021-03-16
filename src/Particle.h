#ifndef PARTICLE_H_
#define PARTICLE_H_

//#include "Pythia8/Pythia.h"
//#include "../fjcore/fjcore.hh"
#include "fastjet/PseudoJet.hh"
#include <vector>
#include <memory>


class Particle{
public:
    Particle(int pid, int stat, int tag,
             std::vector<double> p );
    Particle(int pid, int stat, int tag,
             double e, double px, double py, double pz);
    ~Particle();
    
    std::vector<double> p();
    double perp();
    double e();
    double px();
    double py();
    double pz();
    double modp2();
    double modp();
    double eta();
    double rapidity();
    
    
    
    void ResetAll(int pid, int stat, int tag,
                  double e, double px, double py, double pz);
    void ResetAll(int pid_in, int stat_in, int tag_in,
                  std::vector<double> p );
    void ResetFourMomentum(double e,
                           double px,
                           double py,
                           double pz);
    void ResetFourMomentum(double*p);
    void ResetFourMomentum(std::vector<double> p);
    void ResetStat(int stat_in);
    void ResetPid(int pid_in);
    void ResetTag(int tag_in);
    
    int GetPID(){return pid;}
    int GetStat(){return stat;}
    int GetTag(){return tag;}
    fastjet::PseudoJet GetPseudoJet(){return pseudo_jet;}
    
private:
    
    int pid;
    int stat;
    int tag;
    fastjet::PseudoJet pseudo_jet;
    
    
};

#endif 
