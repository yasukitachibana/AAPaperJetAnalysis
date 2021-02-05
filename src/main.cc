#include "JetAnalysis.h"



//#include <fstream>
// main program
int main(int argc, char *argv[]) {

    int StartTime = time(NULL);
    //#######################################################
    
    std::cout << std::endl;
    std::cout<<"#########################################################"<<std::endl;
    std::cout << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "- Jet Analysis Code -" << std::endl;
    std::cout << "  Yasuki  Tachibana " << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << std::endl;

    if(argc<4){
        std::cout << "Please Specify XML File, input directory and output directory" << std::endl;
        std::cout << ".Main [XML File] [input directory] [output directory]" << std::endl;
    }else{
        std::string xml_filename = argv[1];
        std::string input_dirname = argv[2];
        std::string output_dirname = argv[3];
        JetAnalysis ja(xml_filename,input_dirname,output_dirname);
        ja.Run();
    }
    //#######################################################
    std::cout << std::endl;
    std::cout<<"#########################################################"<<std::endl;
    int EndTime = time(NULL);
    int Hour = (EndTime-StartTime)/3600;
    int Minute = ((EndTime-StartTime)/60)-Hour*60;
    int Second = (EndTime-StartTime)-Hour*60*60 - Minute*60;
    std::cout<<"Programme run time = "<<Hour<<"::"<<Minute<<"::"<<Second<<std::endl;
    std::cout<<"#########################################################"<<std::endl;
    std::cout << std::endl;

    return(0);
}  /* main */

