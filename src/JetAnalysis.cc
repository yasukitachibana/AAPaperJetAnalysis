#include "JetAnalysis.h"
#include "AnalyzeEvents.h"
#include "CombineEvents.h"
#include "SetXML.h"
#include "SetFile.h"

JetAnalysis::JetAnalysis
 (std::string xml_filename_in,
  std::string input_dirname_in,
  std::string output_dirname_in):
xml_filename(xml_filename_in),
input_dirname(input_dirname_in),
output_dirname(output_dirname_in)
{
  std::cout << "-@-Creating JetAnalysis"<<std::endl;
  std::cout <<  "=========================================================" << std::endl;
  SetXML::Instance()->OpenXMLFile(xml_filename);
  std::cout <<  "=========================================================" << std::endl;
  SetFile::Instance()->Init(input_dirname, output_dirname);
  std::cout <<  "=========================================================" << std::endl;
}

JetAnalysis::JetAnalysis(){
  std::cout << "-@-Creating JetAnalysis"<<std::endl;
}

JetAnalysis::~JetAnalysis(){
  std::cout << "-$-Deleting JetAnalysis"<<std::endl;
}


void JetAnalysis::Run(){
  
  
  running_mode = SetXML::Instance()->GetElementInt({"mode"});
  
  std::cout <<  "=========================================================" << std::endl;
  std::cout << "[JetAnalysis]  Start JetAnalysis" << std::endl;
  std::cout <<  "=========================================================" << std::endl;
  
  if( running_mode == 0 || running_mode == 1 ){
    std::cout << "[JetAnalysis]  -Event Analysis-" << std::endl;
    AnalyzeEvents ae;
    ae.Init();
    ae.Analyze();
  }else{
    std::cout << "[JetAnalysis]  Skip Event Analysis " << std::endl;
  }
  std::cout <<  "=========================================================" << std::endl;
  if( running_mode == 0 || running_mode == 2 ){
    std::cout << "[JetAnalysis]  -Combine-" << std::endl;
    CombineEvents ce;
    ce.Combine();
  }else{
    std::cout << "[JetAnalysis]  Skip Combine " << std::endl;
  }
  std::cout <<  "=========================================================" << std::endl;
  
}
