#include "Histogram.h"
#include "SetXML.h"
#include "SetFile.h"

Histogram::Histogram(std::string histname_in): histname(histname_in){
    //std::cout << "-@-Creating Histogram"<<std::endl;
}

Histogram::~Histogram(){
    //std::cout << "-$-Deleting Histogram"<<std::endl;
}


std::string Histogram::HistName(){
    return histname;
}

void Histogram::Init(){
    
    //std::cout << "[Histogram] Initialize "<< histname <<std::endl;
    
    nJet = 0.0;
    nEv = 0.0;
    
    std::vector<double> binEdges_in = SetXML::Instance()->GetElementVectorDouble({"binEdges","Item"});
    
    nBin = binEdges_in.size()-1;
    binEdges = new double[nBin+1];
    
    for(int i=0; i<nBin+1; i++){
        binEdges[i] = binEdges_in[i];
    }
    
    Hist = new TH1D( histname.c_str(), histname.c_str(), nBin, binEdges);
    
}

void Histogram::Fill(double x, double y){
    Hist->Fill( x, y );
}

void Histogram::Print(){
    Print("");
}

void Histogram::Print(std::string name, bool addHistname /* = true */ ){
    
    if(addHistname){
        name += histname;
    }
    
    std::string outfile_path = SetFile::Instance()->GetOutPath( name + ".txt" );
    std::cout << "[Histogram] Creating Output File:"<< outfile_path <<std::endl;
    
    std::ofstream ofs;
    ofs.open( outfile_path.c_str(),
             std::ios::out|std::ios::binary|std::ios::trunc);
    
    ofs << "# x_low x_center x_high value error n_jet n_event"<<std::endl;
    ofs <<  std::setprecision(16);
    
    int nbins = Hist->GetNbinsX();
    
    for (int i=1; i<nbins+1; i++){
        
        double x_c = Hist->GetBinCenter(i);
        double width = Hist->GetBinWidth(i);
        
        ofs
        << (x_c - 0.5*width) << " "
        << x_c << " "
        << (x_c + 0.5*width) << " "
        << Hist->GetBinContent(i) << " "
        << Hist->GetBinError(i) << " "
        << nJet << " "
        << nEv << "\n";
        
    }
    
    ofs.close();
    
}

void Histogram::LoadHistFromFile(){
    
    std::string outfile_path = SetFile::Instance()->GetOutPath(histname+".txt");
    std::cout << "[Histogram] Loading File:"<< outfile_path <<std::endl;
    
    
    
    // Read file
    std::ifstream ifs;
    std::stringstream str_stream;
    
    ifs.open(outfile_path.c_str()); //open the input file
    str_stream << ifs.rdbuf(); //read the file
    if (ifs.is_open()){
        ifs.close();
    }else{
        ifs.close();
        std::cout << "[Histogram] " << outfile_path << " NOT FOUND" <<std::endl;
        return;
    }
    
    std::string str;
    
    double x_l, x_c, x_h, con, err, njet, nev;
    
    
    int i=1;
    while ( getline( str_stream, str ) ){
        
        if( str.find("#") == std::string::npos && ! str.empty() ){
            
            sscanf(str.data(),
                   "%lf %lf %lf %lf %lf %lf %lf",
                   &x_l, &x_c, &x_h, &con, &err, &njet, &nev);
            
            Hist->SetBinContent(i, con);
            Hist->SetBinError(i, err);
            nJet = njet;
            nEv = nev;
            i++;

        }
    }
}


void Histogram::SetSigma(double sigma_in, double sigma_err_in){
    sigma = sigma_in;
    sigma_err = sigma_err_in;
}

double Histogram::GetNjetSigmaOverEev(){
    return sigma*nJet/nEv;
}

void Histogram::Scale(double factor, std::string width  /* = "" */ ){
    if(width == "width"){
        Hist->Scale(factor, "width");
    }else{
        Hist->Scale(factor);
    }
}

void Histogram::Normalize(std::string width  /* = "" */){
    
    double norm, norm_error;
    
    if( width == "width" ){
        norm = Hist->IntegralAndError(1,nBin,norm_error,"width");
    }else{
        norm = Hist->IntegralAndError(1,nBin,norm_error);
    }
    
    DivideWithError( norm, norm_error );
    
}


void Histogram::DivideWithError( double norm, double norm_error )
{
    
    TH1D *Norm = new TH1D( "_norm_hist", "_norm_hist", nBin, binEdges);
    
    int nbins = Hist->GetNbinsX();
    for (int i=1; i<nbins+1; i++){
        Norm->SetBinContent(i, norm);
        Norm->SetBinError(i, norm_error);
    }

    Hist->Divide(Norm);
    delete Norm;
    
}














void Histogram::Add(TH1D *h){
    Hist->Add(h);
}

void Histogram::Add(TH1D *h, double factor){
    Hist->Add(h, factor);
}

void Histogram::Add(std::shared_ptr<Histogram> h){
    Hist->Add(h->GetTH1D());
}

void Histogram::Add(std::shared_ptr<Histogram> h, double factor){
    Hist->Add(h->GetTH1D(), factor);
}


















//
//
//void Histogram::CheckPrintHist(){
//
//    int nbins = jsHist->GetNbinsX();
//    std::cout<<"\nhist\n";
//    for (int i=1; i<nbins+1; i++){
//
//
//        std::cout
//        << jsHist->GetBinCenter(i) << " "
//        << jsHist->GetBinContent(i) << std::endl;
//
//    }
//
//}





//void Histogram::SetSigma(double sigma_in, double sigma_error_in){
//
//    sigma = sigma_in;
//    sigma_error = sigma_error_in;
//
//}
//
//void Histogram::Out(std::string label, std::string out_dir){
//
//    if(N_jet>0){
//
//        jsHist->Scale((1.0/N_jet));
//        std::string filename
//        = out_dir +"/"+label+"_non_deriv.txt";
//        Print(filename);
//
//        jsHist->Scale(1.0,"width");
//        filename
//        = out_dir +"/"+label+"_raw.txt";
//        Print(filename);
//
//        Normalize();
//        filename
//        = out_dir +"/"+label+"_normalized.txt";
//        Print(filename);
//
//    }else{
//        std::cout << " No Jet. End. "<<std::endl;
//    }
//
//
//}
//
//void Histogram::Normalize(){
//
//    double norm_error;
//    double norm
//    = jsHist->IntegralAndError(1,Nbin,norm_error,"width");
//    jsHist->Scale((1.0/norm));
//
//}
//
//
//
