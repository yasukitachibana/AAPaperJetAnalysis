#ifndef LOADJETSCAPEASCII_H_
#define LOADJETSCAPEASCII_H_
#include "LoadFileBase.h"



class LoadJetScapeAscii: public LoadFileBase {
public:
    LoadJetScapeAscii();
    ~LoadJetScapeAscii();
    
    void Load(std::string input_filename);
    int GetLine();
    void ShowLine();
    int EventEnd();
    int ValidLine();
    int Last(){return 1;}
    void LoadSigma(std::string sigma_filename, double &sigma, double &sigma_err);

    
    std::shared_ptr<Particle> GetParticle();

    
private:



    std::stringstream input_str_stream;
    std::string input_line;
    
    int getLineStart;
    
    int SN, PID;
    double Px, Py, Pz, E, Eta, Phi;
    int Status;

    


};

#endif 
