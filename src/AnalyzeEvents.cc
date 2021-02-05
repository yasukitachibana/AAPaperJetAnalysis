#include "AnalyzeEvents.h"
#include "SetXML.h"
#include "SetFile.h"

AnalyzeEvents::AnalyzeEvents(){
    std::cout << "-@-Creating AnalyzeEvents"<<std::endl;
}


AnalyzeEvents::~AnalyzeEvents(){
    std::cout << "-$-Deleting AnalyzeEvents"<<std::endl;
}

void AnalyzeEvents::Init(){
    std::cout << "[AnalyzeEvents] Intialize AnalyzeEvents"<<std::endl;
    
    ptHat = SetXML::Instance()->GetElementVectorDouble({"ptHat","Item"});
    nPtHatBin = ptHat.size()-1;
    observable = SetXML::Instance()->GetElementText({"observable"});
    
    
    if( observable == "jetshape") {
        std::cout << "[AnalyzeEvents] jet shape analysis" << std::endl;
        analyze_ptr = std::unique_ptr<JetShape> (new JetShape());
        analyze_ptr->Init();
    }
    
    
}

void AnalyzeEvents::Analyze(){
    
    std::cout << "[AnalyzeEvents] Start AnalyzeEvents"<<std::endl;
    
    for(int i_pthat_bin = 0; i_pthat_bin < nPtHatBin; i_pthat_bin++ ){
        
        std::cout <<  "=========================================================" << std::endl;
        std::cout << "[AnalyzeEvents] ptHatBin: " << ptHat[i_pthat_bin] << "-" << ptHat[i_pthat_bin+1] << "GeV"  << std::endl;

        //++++++++++++++++++++++++++++++++++++++++++++++++
        //++++++++++++++++++++++++++++++++++++++++++++++++
        analyze_ptr->Start(ptHat[i_pthat_bin],ptHat[i_pthat_bin+1]);
        //++++++++++++++++++++++++++++++++++++++++++++++++
        for(int i_seq = 0; i_seq < 1; i_seq++ ){

            std::string input_file_name =  SetFile::Instance()->GetInputFileName(ptHat[i_pthat_bin], ptHat[i_pthat_bin+1]);
            
            analyze_ptr->Analyze(input_file_name);
            
        }
        //++++++++++++++++++++++++++++++++++++++++++++++++
        analyze_ptr->End();
        //++++++++++++++++++++++++++++++++++++++++++++++++
        //++++++++++++++++++++++++++++++++++++++++++++++++

        
        std::cout <<  "=========================================================" << std::endl;
    }
    
    std::cout << "[AnalyzeEvents] Done AnalyzeEvents"<<std::endl;
    
}
