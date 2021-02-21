#include "Hist1D.h"



Hist1D::~Hist1D(){
    //std::cout << "-$-Deleting Hist1D"<<std::endl;
}

void Hist1D::InitHist(){
  
  std::vector<double> binEdges_in = SetXML::Instance()->GetElementVectorDouble({"binEdges","Item"});
  
  nBin = binEdges_in.size()-1;
  binEdges = new double[nBin+1];
  
  for(int i=0; i<nBin+1; i++){
    binEdges[i] = binEdges_in[i];
  }
  
  Hist = new TH1D( histname.c_str(), histname.c_str(), nBin, binEdges);


}

void Hist1D::Fill(double x, double y){
  Hist->Fill( x, y );
}

void Hist1D::Print(std::string name, bool addHistname /* = true */ ){
  
  if(addHistname){
    name += histname;
  }
  
  std::string outfile_path = SetFile::Instance()->GetOutPath( name + ".txt" );
  std::cout << "[Hist1D] Creating Output File:"<< outfile_path <<std::endl;
  
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

void Hist1D::LoadHistFromFile(){
  
  std::string outfile_path = SetFile::Instance()->GetOutPath(histname+".txt");
  std::cout << "[Hist1D] Loading File:"<< outfile_path <<std::endl;
  
  
  
  // Read file
  std::ifstream ifs;
  std::stringstream str_stream;
  
  ifs.open(outfile_path.c_str()); //open the input file
  str_stream << ifs.rdbuf(); //read the file
  if (ifs.is_open()){
    ifs.close();
  }else{
    ifs.close();
    std::cout << std::endl;
    std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
    std::cout << "[Hist1D] " << outfile_path << " NOT FOUND" <<std::endl;
    std::cout << "[Hist1D] Exit. "<< std::endl;
    std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
    std::cout << std::endl;
    exit(-1);
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


void Hist1D::Scale(double factor, std::string width  /* = "" */ ){
  if(width == "width"){
    Hist->Scale(factor, "width");
  }else{
    Hist->Scale(factor);
  }
}

void Hist1D::Normalize(std::string width  /* = "" */){

  double norm, norm_error;
  
  if( width == "width" ){
    norm = Hist->IntegralAndError(1,nBin,norm_error,"width");
  }else{
    norm = Hist->IntegralAndError(1,nBin,norm_error);
  }
  
  DivideWithError( norm, norm_error );
  
}

void Hist1D::DivideWithError( double norm, double norm_error )
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

void Hist1D::Add(TH1D *h){
  Hist->Add(h);
}

void Hist1D::Add(TH1D *h, double factor){
  Hist->Add(h, factor);
}

void Hist1D::Add(std::shared_ptr<Histogram> h){
  Add(std::dynamic_pointer_cast<Hist1D>(h)->GetTH1D());
}

void Hist1D::Add(std::shared_ptr<Histogram> h, double factor){
  Add(std::dynamic_pointer_cast<Hist1D>(h)->GetTH1D(), factor);
}

