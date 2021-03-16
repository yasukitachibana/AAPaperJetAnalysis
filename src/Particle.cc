#include "Particle.h"

Particle::Particle(int pid_in, int stat_in, int tag_in,
                   double e, double px, double py, double pz){
    
    pid = pid_in;
    stat = stat_in;
    tag = tag_in;
    pseudo_jet = fastjet::PseudoJet(px,py,pz,e);
    
}

Particle::Particle(int pid_in, int stat_in, int tag_in, std::vector<double> p )
{
    
    pid = pid_in;
    stat = stat_in;
    tag = tag_in;
    pseudo_jet = fastjet::PseudoJet(p[1],p[2],p[3],p[0]);
    
}

Particle::~Particle(){
    //std::cout << "-$-p ("<< tag <<") delete"<<std::endl;
}// destructor

void Particle::ResetAll(int pid_in, int stat_in, int tag_in, std::vector<double> p ){
    pid = pid_in;
    stat = stat_in;
    tag = tag_in;
    pseudo_jet.reset(p[1],p[2],p[3],p[0]);
}

void Particle::ResetAll(int pid_in, int stat_in, int tag_in,
                        double e, double px, double py, double pz){
    pid = pid_in;
    stat = stat_in;
    tag = tag_in;
    pseudo_jet.reset(px,py,pz,e);
}

void Particle::ResetFourMomentum(double e,
                                 double px,
                                 double py,
                                 double pz){
    pseudo_jet.reset(px,py,pz,e);
}

void Particle::ResetFourMomentum(double*p){
    pseudo_jet.reset(p[1],p[2],p[3],p[0]);
}

void Particle::ResetFourMomentum(std::vector<double> p){
    pseudo_jet.reset(p[1],p[2],p[3],p[0]);
}


void Particle::ResetStat(int stat_in){
    stat = stat_in;
}

void Particle::ResetPid(int pid_in){
    pid = pid_in;
}

void Particle::ResetTag(int tag_in){
    tag = tag_in;
}

std::vector<double> Particle::p(){
    std::vector<double>
    p{  pseudo_jet.e(),
        pseudo_jet.px(),
        pseudo_jet.py(),
        pseudo_jet.pz()};
    return p;
}

double Particle::perp(){
    return pseudo_jet.perp();
}


double Particle::e(){
    return pseudo_jet.e();
}

double Particle::px(){
    return pseudo_jet.px();
}

double Particle::py(){
    return pseudo_jet.py();
}

double Particle::pz(){
    return pseudo_jet.pz();
}

double Particle::modp2(){
    return pseudo_jet.modp2();
}

double Particle::modp(){
    return sqrt(pseudo_jet.modp2());
}

double Particle::rapidity(){
    return pseudo_jet.rapidity();
}

double Particle::eta(){
    return pseudo_jet.eta();
}
