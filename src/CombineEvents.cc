#include "CombineEvents.h"
#include "CombineJetShape.h"

CombineEvents::CombineEvents(){
    std::cout << "-@-Creating CombineEvents"<<std::endl;
}


CombineEvents::~CombineEvents(){
    std::cout << "-$-Deleting CombineEvents"<<std::endl;
}


void CombineEvents::Init(){
    observable = SetXML::Instance()->GetElementText({"observable"});    std::cout << "[CombineEvents] Start CombineEvents"<<std::endl;
    if( observable == "jetshape") {
        std::cout << "[CombineEvents] Combine jet shape results" << std::endl;
        combine_ptr = std::unique_ptr<CombineJetShape> (new CombineJetShape());
        combine_ptr->Init();
    }

}

void CombineEvents::Combine(){

    Init();
    std::cout <<  "=========================================================" << std::endl;

    combine_ptr->Combine();
    
    std::cout <<  "=========================================================" << std::endl;
    
    std::cout << "[CombineEvents] Done CombineEvents"<<std::endl;
    
}

