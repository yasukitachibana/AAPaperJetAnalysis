#ifndef JETANALYSIS_H_
#define JETANALYSIS_H_


#include <iostream>

class JetAnalysis{
public:
  JetAnalysis();
  JetAnalysis(std::string xml_filename, std::string input_dirname, std::string output_dirname);
  ~JetAnalysis();
  void Run();
  
private:
  const std::string xml_filename = "test.xml";
  const std::string input_dirname = "./";
  const std::string output_dirname = "./";
  int running_mode;
  
};

#endif 
