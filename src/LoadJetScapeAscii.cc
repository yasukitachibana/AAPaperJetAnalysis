#include "LoadJetScapeAscii.h"
#include "SetXML.h"
#include "SetFile.h"


LoadJetScapeAscii::LoadJetScapeAscii(){
    std::cout << "-@-Creating LoadJetScapeAscii"<<std::endl;
}

LoadJetScapeAscii::~LoadJetScapeAscii(){
    std::cout << "-$-Deleting LoadJetScapeAscii"<<std::endl;
}


std::shared_ptr<Particle> LoadJetScapeAscii::GetParticle(){
    
    if(test_tag == 1){
        ShowLine();
        test_tag = 0;
    }
    
    sscanf(input_line.data(),
           "%d %d %d %lf %lf %lf %lf %lf %lf",
           &SN, &PID, &Status, &E, &Px, &Py, &Pz, &Eta, &Phi);
    
    auto particle = std::make_shared<Particle>(PID,Status,0,E,Px,Py,Pz);

    return particle;
}

void LoadJetScapeAscii::Load(std::string input_filename){
    
    input_line.clear();
    input_line.shrink_to_fit();
    input_str_stream.str("");
    input_str_stream.clear(std::stringstream::goodbit);
    
    std::cout << "[LoadJetScapeAscii] Load: " << input_filename <<std::endl;

    std::ifstream ifs;
    ifs.open(input_filename.c_str()); //open the input file
    input_str_stream << ifs.rdbuf(); //read the file

    if (ifs.is_open()){
        ifs.close();
    }else{
        ifs.close();
        std::cout << std::endl;
        std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
        std::cout << "[LoadJetScapeAscii] InputFile: " << input_filename << " is not found" <<std::endl;
        std::cout << "[LoadJetScapeAscii] Exit. "<< std::endl;
        std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
        std::cout << std::endl;
        exit(-1);
        
    }
    
    std::cout << "[LoadJetScapeAscii]  File Loaded. " <<std::endl;
    getLineStart = 0;
    
}

int LoadJetScapeAscii::GetLine(){
    
    if(getline(input_str_stream, input_line)){
        return 1;
    }else{
        return 0;
    }
    
}

int LoadJetScapeAscii::EventEnd(){
    if( input_line.find("#") != std::string::npos && getLineStart == 1 ){
        return 1;
    }else{
        getLineStart = 1;
        return 0;
    }
}


int LoadJetScapeAscii::ValidLine(){
    if( input_line.find("#") == std::string::npos && ! input_line.empty() ){
        return 1;
    }else{
        return 0;
    }
}


void LoadJetScapeAscii::ShowLine(){
    std::cout << "[LoadJetScapeAscii] Now Line: " << input_line <<std::endl;
}


void LoadJetScapeAscii::LoadSigma(std::string sigma_filename, double &sigma, double &sigma_err){
    
    // Read file
    std::ifstream ifs;
    std::stringstream str_stream;
    
    ifs.open(sigma_filename.c_str()); //open the input file
    str_stream << ifs.rdbuf(); //read the file
    if (ifs.is_open()){
        ifs.close();
    }else{
        ifs.close();
        std::cout << "[LoadJetScapeAscii] " << sigma_filename << " NOT FOUND" <<std::endl;
        return;
    }
    
    std::string str;
    
    while ( getline( str_stream, str ) ){
        
        if( str.find("#") == std::string::npos && ! str.empty() ){
            
            sscanf(str.data(),
                   "%lf %lf",
                   &sigma, &sigma_err);
            break;

        }
    }
}
