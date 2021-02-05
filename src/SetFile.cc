#include "SetFile.h"
#include "SetXML.h"
//#include "JetScapeLogger.h"
//#include <stdlib.h>

#include <sstream>
#include <iomanip>


SetFile* SetFile::m_pInstance = NULL;

SetFile* SetFile::Instance() {
    if (!m_pInstance)
    {
        std::cout<<"[SetFile] Created SetFile Instance"<<std::endl;
        m_pInstance = new SetFile();
    }
    return m_pInstance;
}

void SetFile::Init(std::string m_in_name, std::string m_out_name){
    SetDir(m_in_name, m_out_name);
    
    input_head = SetXML::Instance()->GetElementText({"inputHead"});
    input_join = SetXML::Instance()->GetElementText({"inputJoin"});
    input_tail = SetXML::Instance()->GetElementText({"inputTail"});
    
    sigma_head = SetXML::Instance()->GetElementText({"sigmaHead"});
    sigma_join = SetXML::Instance()->GetElementText({"sigmaJoin"});
    sigma_tail = SetXML::Instance()->GetElementText({"sigmaTail"});
    
}

void SetFile::SetDir(std::string m_in_name, std::string m_out_name){
    SetInputDir(m_in_name);
    SetOutputDir(m_out_name);
}

std::string
SetFile::GetInputFileName( double ptHatMin, double ptHatMax ){
    return in_dir+'/'+input_head + std::to_string(int(ptHatMin)) + input_join + std::to_string(int(ptHatMax)) + input_tail;
}



std::string
SetFile::GetSigmaFileName( double ptHatMin, double ptHatMax ){
    return in_dir+'/'+sigma_head + std::to_string(int(ptHatMin)) + sigma_join + std::to_string(int(ptHatMax)) + sigma_tail;
}





std::string
SetFile::GetHistName(double ptHatMin, double ptHatMax,
                     double jetPtMin, double jetPtMax,
                     double jetRapMin, double jetRapMax,
                     double hadPtMin, double hadPtMax,
                     double hadRapMin, double hadRapMax){
    
    std::ostringstream oss;
    
    oss << std::fixed
    << "hist_" << "ptHat" << std::setprecision(0) << (ptHatMin) << "-" << (ptHatMax) << "_"
    << "ptj" << std::setprecision(0) << (jetPtMin) << "-" << (jetPtMax) << "_"
    << "rapj" << std::setprecision(1) << (jetRapMin) << "-" << (jetRapMax) << "_"
    << "pt" << std::setprecision(1) << (hadPtMin) << "-" << (hadPtMax) << "_"
    << "rap" << std::setprecision(1) << (hadRapMin) << "-" << (hadRapMax);
    
    return oss.str();
    
}


std::string
SetFile::GetHistName(double jetPtMin, double jetPtMax,
                     double jetRapMin, double jetRapMax,
                     double hadPtMin, double hadPtMax,
                     double hadRapMin, double hadRapMax){
    
    std::ostringstream oss;
    
    oss << std::fixed
    << "hist_total_"
    << "ptj" << std::setprecision(0) << (jetPtMin) << "-" << (jetPtMax) << "_"
    << "rapj" << std::setprecision(1) << (jetRapMin) << "-" << (jetRapMax) << "_"
    << "pt" << std::setprecision(1) << (hadPtMin) << "-" << (hadPtMax) << "_"
    << "rap" << std::setprecision(1) << (hadRapMin) << "-" << (hadRapMax);
    
    return oss.str();
    
}

std::string SetFile::GetOutPath(std::string name){
    return out_dir+'/'+ name;
}
