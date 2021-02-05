
#ifndef SETFILE_H
#define SETFILE_H

#include<string>
#include<iostream>
#include <vector>
//#include<stdexcept>

#include "../tinyxml2/tinyxml2.h"

class SetFile{
public:
    static SetFile* Instance();
    
    void SetInputDir(std::string m_in_name) {
        in_dir = m_in_name;
        std::cout << "[SetFile] Input File Directory: "<< in_dir << std::endl;
    }
    
    void SetOutputDir(std::string m_out_name) {
        out_dir = m_out_name;
        std::cout << "[SetFile] Output File Directory: "<< out_dir << std::endl;
    }
    
    void Init(std::string m_in_name, std::string m_out_name);
    void SetDir(std::string m_in_name, std::string m_out_name);
    
    std::string
    GetInputFileName( double ptHatMin, double ptHatMax );
    
    std::string
    GetSigmaFileName( double ptHatMin, double ptHatMax );
    
    
    std::string
    GetHistName(double ptHatMin, double ptHatMax,
                double jetPtMin, double jetPtMax,
                double jetRapMin, double jetRapMax,
                double hadPtMin, double hadPtMax,
                double hadRapMin, double hadRapMax);
    
    std::string
    GetHistName(double jetPtMin, double jetPtMax,
                double jetRapMin, double jetRapMax,
                double hadPtMin, double hadPtMax,
                double hadRapMin, double hadRapMax);
    
    std::string GetOutPath(std::string name);
    
    
private:
    SetFile(){
        std::cout << "-@-Creating SetFile"<<std::endl;
    };
    
    SetFile(SetFile const&){
    };
    
    static SetFile* m_pInstance;
    std::string in_dir;
    std::string out_dir;
    std::string input_head;
    std::string input_join;
    std::string input_tail;
    std::string sigma_head;
    std::string sigma_join;
    std::string sigma_tail;
    
    
};
#endif

