#include "CombineEvents.h"
#include "CombineJetSpec.h"
#include "CombineHadSpec.h"
#include "CombineJetShape.h"
#include "CombineJetShapeSub.h"
#include "CombineFfPt.h"
#include "CombineFfZ.h"

CombineEvents::CombineEvents(){
    std::cout << "-@-Creating CombineEvents"<<std::endl;
}


CombineEvents::~CombineEvents(){
    std::cout << "-$-Deleting CombineEvents"<<std::endl;
}


void CombineEvents::Init(){
    observable = SetXML::Instance()->GetElementText({"observable"});    std::cout << "[CombineEvents] Start CombineEvents"<<std::endl;
    
    if( observable == "hadspec") {
        std::cout << "[CombineEvents] Combine particle spectrum" << std::endl;
        combine_ptr = std::unique_ptr<CombineHadSpec> (new CombineHadSpec());
    }else if( observable == "jetspec") {
        std::cout << "[CombineEvents] Combine jet spectrum" << std::endl;
        combine_ptr = std::unique_ptr<CombineJetSpec> (new CombineJetSpec());
    }else if( observable == "jetshape") {
        std::cout << "[CombineEvents] Combine jet shape" << std::endl;
        combine_ptr = std::unique_ptr<CombineJetShape> (new CombineJetShape());
    }else if( observable == "jetshapesub") {
      std::cout << "[CombineEvents] Combine jet shape w/ subtraction" << std::endl;
      combine_ptr = std::unique_ptr<CombineJetShapeSub> (new CombineJetShapeSub());
  }else if( observable == "ffpt") {
        std::cout << "[CombineEvents] Combine fragmentation function (pt)" << std::endl;
        combine_ptr = std::unique_ptr<CombineFfPt> (new CombineFfPt());
    }else if( observable == "ffz") {
        std::cout << "[CombineEvents] Combine fragmentation function (z)" << std::endl;
        combine_ptr = std::unique_ptr<CombineFfZ> (new CombineFfZ());
    }else{
        std::cout << std::endl;
        std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
        std::cout << "[CombineEvents] Observable: " << observable << " is not suported" << std::endl;
        std::cout << "[CombineEvents] Exit. "<< std::endl;
        std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
        std::cout << std::endl;
        exit(-1);
    }
    
    combine_ptr->Init();
    
    

}

void CombineEvents::Combine(){

    Init();
    std::cout <<  "=========================================================" << std::endl;

    combine_ptr->Combine();
    
    std::cout <<  "=========================================================" << std::endl;
    
    std::cout << "[CombineEvents] Done CombineEvents"<<std::endl;
    
}

