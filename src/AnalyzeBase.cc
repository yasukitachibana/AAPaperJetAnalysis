#include "AnalyzeBase.h"
#include "SetXML.h"
#include "SetFile.h"
#include "Particle.h"

#include <sys/time.h>
#include <sys/resource.h>


AnalyzeBase::~AnalyzeBase(){
    std::cout << "-$-Deleting AnalyzeBase"<<std::endl;
}

void AnalyzeBase::Init()
{

    std::cout
    << "[AnalyzeBase] Intialize "
    << ObservableName()
    <<std::endl;
    
    InitSettings();
    SetJetPtCut();
    SetLargestRapidity();
    
    
    if( subMethod == "negative" || subMethod == "Negative" ||
       subMethod == "negatives" || subMethod == "Negatives" ||
       subMethod == "neg" || subMethod == "Neg" ) {
        
        std::cout << "[AnalyzeEvents] Standard Negative Particle Subtraction" << std::endl;
        sub_ptr = std::unique_ptr<SubNegatives> (new SubNegatives());
    }else{
        sub_ptr = std::unique_ptr<SubtractionBase> (new SubtractionBase());
    }
    
    chMin=0.0001;
    
}

void AnalyzeBase::Start(double ptHatMin, double ptHatMax)
{

    GenerateHist(ptHatMin, ptHatMax);
    InitHist();
    
}

void AnalyzeBase::End()
{
    for( auto hist: hist_list){
        hist->Print();
    }
    DeleteHist();
    //std::cout<<"[AnalyzeEvents] Refresh ("<<std::to_string(getMemoryUsage())<<"MB) ..."<< std::endl;
}



void AnalyzeBase::GenerateHist(double ptHatMin, double ptHatMax){
    
    int nHist = 0;
    
    for( int i_jet_pt = 0; i_jet_pt < jetPtMin.size(); i_jet_pt++ ){
        for( int i_jet_rap = 0; i_jet_rap < jetRapMin.size(); i_jet_rap++ ){
            for( int i_had_pt = 0; i_had_pt < hadPtMin.size(); i_had_pt++ ){
                for( int i_had_rap = 0; i_had_rap < hadRapMin.size(); i_had_rap++ ){

                    std::string hist_name = GetHistName(ptHatMin, ptHatMax, i_jet_pt, i_jet_rap, i_had_pt, i_had_rap);
                    std::cout << "[AnalyzeBase] generate histogram #" << nHist << " " << hist_name << std::endl;
                    
                    auto hist_this_bin = std::make_shared<Histogram>(hist_name);
                    hist_list.push_back(hist_this_bin);

                    nHist ++;
                    //std::cout << GetHist(i_jet_pt, i_jet_rap, i_had_pt, i_had_rap)->HistName() << std::endl;
                    
                }//had_rap
            }//had_pt
        }//jet_rap
    }//jet_pt

    std::cout << "[AnalyzeBase] number of generated histogram: " << nHist << std::endl;
    
}

void AnalyzeBase::InitHist(){
    for( auto hist: hist_list ){
        hist->Init();
    }
}

void AnalyzeBase::DeleteHist(){
    
    for( auto hist: hist_list ){
        hist->DeleteTH1D();
    }
    
    hist_list.clear();
    hist_list.shrink_to_fit();
}



std::string AnalyzeBase::GetHistName(double ptHatMin, double ptHatMax, int i_jet_pt, int i_jet_rap, int i_had_pt, int i_had_rap){
    
    return SetFile::Instance()->GetHistName(ptHatMin, ptHatMax,
                                            jetPtMin[i_jet_pt], jetPtMax[i_jet_pt],
                                            jetRapMin[i_jet_rap], jetRapMax[i_jet_rap],
                                            hadPtMin[i_had_pt], hadPtMax[i_had_pt],
                                            hadRapMin[i_had_rap], hadRapMax[i_had_rap]);
    
}


std::shared_ptr<Histogram> AnalyzeBase::GetHist(int i_jet_pt, int i_jet_rap, int i_had_pt, int i_had_rap){
    int i = hadRapMin.size()*(hadPtMin.size()*(jetRapMin.size()*i_jet_pt + i_jet_rap) + i_had_pt) + i_had_rap;
    //std::cout << "[AnalyzeBase] " << i << std::endl;
    return hist_list[i];
}


void AnalyzeBase::InitSettings(){
    
    jetR = SetXML::Instance()->GetElementDouble({"jetR"});
    chJet = SetXML::Instance()->GetElementInt({"chJet"});
//    primHadPtMin = SetXML::Instance()->GetElementDouble({"primaryHadronPtMin"});
//    chPrimHad = SetXML::Instance()->GetElementInt({"chPrimaryHadron"});
    jetRapidity = SetXML::Instance()->GetElementInt({"jetRapidity"});
    jetRapMin = SetXML::Instance()->GetElementVectorDouble({"jetRapMin","Item"});
    jetRapMax = SetXML::Instance()->GetElementVectorDouble({"jetRapMax","Item"});
    jetPtMin = SetXML::Instance()->GetElementVectorDouble({"jetPtMin","Item"});
    jetPtMax = SetXML::Instance()->GetElementVectorDouble({"jetPtMax","Item"});
    
    chHad = SetXML::Instance()->GetElementInt({"chHadron"});
    hadRapidity = SetXML::Instance()->GetElementInt({"hadronRapidity"});
    hadRapMin = SetXML::Instance()->GetElementVectorDouble({"hadronRapMin","Item"});
    hadRapMax = SetXML::Instance()->GetElementVectorDouble({"hadronRapMax","Item"});
    hadPtMin = SetXML::Instance()->GetElementVectorDouble({"hadronPtMin","Item"});
    hadPtMax = SetXML::Instance()->GetElementVectorDouble({"hadronPtMax","Item"});

    subMethod = SetXML::Instance()->GetElementText({"subtractionMethod"});
    inputStyle = SetXML::Instance()->GetElementText({"inputStyle"});
    
    //*******************************************************************************************
    //*******************************************************************************************
    std::cout << std::endl;
    std::cout << "[AnalyzeBase] **********************************************"<< std::endl;
    std::cout << "[AnalyzeBase] *** Settings"<< std::endl;
    std::cout << "[AnalyzeBase] ***-------------------------------------------"<< std::endl;
    std::cout << "[AnalyzeBase] ***-------------------------------------------"<< std::endl;
    
    std::cout << "[AnalyzeBase] *** R_jet = "<< jetR << ", " << JetType(chJet) << std::endl;
    std::cout << "[AnalyzeBase] *** subtraction: "<< subMethod << std::endl;
//    std::cout << "[AnalyzeBase] *** primary particle pt > "<< primHadPtMin << " GeV" << std::endl;
//    std::cout << "[AnalyzeBase] *** primary: " << HadronType(chPrimHad) << std::endl;
    
    for( int i = 0; i < jetPtMin.size(); i++ ){
        std::cout << "[AnalyzeBase] *** " << jetPtMin[i] << " < pt_jet < " << jetPtMax[i] << " GeV" << std::endl;
    }
    for( int i = 0; i < jetRapMin.size(); i++ ){
        std::cout << "[AnalyzeBase] *** " << jetRapMin[i] << " < |" << RapType(jetRapidity) << "_jet| < " << jetRapMax[i] << std::endl;
    }
    
    std::cout << "[AnalyzeBase] ***-------------------------------------------"<< std::endl;
    std::cout << "[AnalyzeBase] *** "<< HadronType(chHad) << std::endl;
    for( int i = 0; i < hadPtMin.size(); i++ ){
        std::cout << "[AnalyzeBase] *** " << hadPtMin[i] << " < pt < " << hadPtMax[i] << " GeV" << std::endl;
    }
    for( int i = 0; i < hadRapMin.size(); i++ ){
        std::cout << "[AnalyzeBase] *** " << hadRapMin[i] << " < |" << RapType(hadRapidity) << "| < " << hadRapMax[i] << std::endl;
    }
    
    std::cout << "[AnalyzeBase] **********************************************"<< std::endl;
    std::cout << std::endl;
    //*******************************************************************************************
    //*******************************************************************************************
    
    if(chJet == 1 && chHad == 0 ){
        std::cout << std::endl;
        std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
        std::cout << "[AnalyzeBase] Bad Combination: Charged Jet and Charged+Neutral Particles" << std::endl;
        std::cout << "[AnalyzeBase] Exit. "<< std::endl;
        std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
        std::cout << std::endl;
        exit(-1);
    }

    
}

std::string AnalyzeBase::ObservableName(){
    return "AnalyzeBase";
}

std::string AnalyzeBase::JetType(int chJet){
    if(chJet == 1){
        return "Charged Jet";
    }else{
        return "Full Jet";
    }
}

std::string AnalyzeBase::HadronType(int chHad){
    if(chHad == 1){
        return "Charged Particles";
    }else{
        return "Charged+Neutral Particles";
    }
}


std::string AnalyzeBase::RapType(int rap){
    if(rap == 1){
        return "Eta";
    }else{
        return "Y";
    }
}

void AnalyzeBase::Analyze(std::string input_file_name)
{
    std::cout << "[AnalyzeBase] Analyze " << ObservableName() <<" ("<<std::to_string(getMemoryUsage())<<"MB) ..."<< std::endl;
    //*******************************************************************************************
    //*******************************************************************************************
    std::unique_ptr<LoadFileBase> load_file_ptr;
    if(inputStyle == "JetScapeAscii" || inputStyle == "JetscapeAscii" ){
        load_file_ptr = std::unique_ptr<LoadJetScapeAscii> (new LoadJetScapeAscii());
    }else{
        std::cout << std::endl;
        std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
        std::cout << "[AnalyzeBase] Input format, " << inputStyle << ", is not supported." << std::endl;
        std::cout << "[AnalyzeBase] Exit. "<< std::endl;
        std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
        std::cout << std::endl;
        exit(-1);
    }
    //*******************************************************************************************
    //*******************************************************************************************
    
    load_file_ptr->Load(input_file_name);
    
    std::vector<std::shared_ptr<Particle>> particle_list;
    
    int event_num = 0;
    while( load_file_ptr->GetLine() ){
        //load_file_ptr->ShowLine();
        
        if( load_file_ptr->EventEnd() ){
            //load_file_ptr->ShowLine();
            //**************
            //std::cout << "##s" << particle_list.size() << "c" << particle_list.capacity() << std::flush;
            EventEndMark( particle_list, event_num );
            //std::cout << "--s" << particle_list.size() << "c" << particle_list.capacity() << std::flush;
            //**************
            
        }else if( load_file_ptr->ValidLine() ){
            
            auto particle = load_file_ptr->GetParticle();
            if( RapidityCut(particle) &&
                ( chJet == 0 || fabs(pythia.particleData.charge( particle->GetPID() )) > chMin ) )
            {
                particle_list.push_back(particle);
            }
            
        }
        
    }
    
    if( load_file_ptr->Last() ){
    //**************
    EventEndMark( particle_list, event_num );
    //**************
    }
    
    std::cout << "\n[AnalyzeBase] Last Event" << event_num <<" -- DONE! ("<<std::to_string(getMemoryUsage())<<"MB) ..."<< std::endl;

}



void AnalyzeBase::EventEndMark(std::vector<std::shared_ptr<Particle>> &particle_list, int &event_num){

    
    if(event_num%2500==0){
        std::cout
        << "Event" << event_num
        <<" ("<<std::to_string(getMemoryUsage())<<"MB) "<< std::flush;
        if( ((event_num/2500)+1)%5==0 ){
            std::cout<<std::endl;
        }
    }
    
    for( auto hist: hist_list){
        hist->EventCount();
    }

    OneEventAnalysis(particle_list);
    particle_list.clear();
    particle_list.shrink_to_fit();
    event_num++;
    
}

long AnalyzeBase::getMemoryUsage()
{
  struct rusage usage;
  // NOTE: Reported in kB on BSD/Linux, bytes in Mac/Darwin
  // Could try to explicitly catch __linux__ as well
  float mbsize = 1024;
#ifdef __MACH__
  mbsize = 1024 * 1024;
#endif
    
  if(0 == getrusage(RUSAGE_SELF, &usage))
    return usage.ru_maxrss/mbsize;
  else
    return 0;
}

bool AnalyzeBase::HadTrigger(std::shared_ptr<Particle> p, std::vector<std::array<int, 2>> &i_h ){
    
    bool trigger = false;

    if( chHad == 1 && fabs(pythia.particleData.charge( p->GetPID() )) < chMin )
    {
        return trigger;
    }

    double pt = p->perp();
    double rapidity = GetRapidity(p);



    for( int i_had_pt = 0; i_had_pt < hadPtMin.size(); i_had_pt++ ){
        for( int i_had_rap = 0; i_had_rap < hadRapMin.size(); i_had_rap++ ){

            if( pt >= hadPtMin[i_had_pt] &&
               pt < hadPtMax[i_had_pt] &&
               fabs(rapidity) >= hadRapMin[i_had_rap] &&
               fabs(rapidity) < hadRapMax[i_had_rap] ){

                std::array<int, 2> ih = {i_had_pt,i_had_rap};
                i_h.push_back(ih);

                trigger = true;

            }


        }//rap
    }//pt

    return trigger;
}


bool AnalyzeBase::JetTrigger(fjcore::PseudoJet jet, std::vector<std::array<int, 2>> &i_j ){
    
    double pt_jet = jet.perp();
    double rapidity_jet = GetRapidity(jet);
    
    bool trigger = false;
    for( int i_jet_pt = 0; i_jet_pt < jetPtMin.size(); i_jet_pt++ ){
        for( int i_jet_rap = 0; i_jet_rap < jetRapMin.size(); i_jet_rap++ ){
            
            if( pt_jet >= jetPtMin[i_jet_pt] &&
               pt_jet < jetPtMax[i_jet_pt] &&
               fabs(rapidity_jet) >= jetRapMin[i_jet_rap] &&
               fabs(rapidity_jet) < jetRapMax[i_jet_rap] ){
                
                std::array<int, 2> ij = {i_jet_pt,i_jet_rap};
                i_j.push_back(ij);
                trigger = true;
                
            }
            
        }//jet_rap
    }//jet_pt
    
    return trigger;
}

void AnalyzeBase::OneEventAnalysis(std::vector<std::shared_ptr<Particle>> particle_list){
    
    
    std::vector <fjcore::PseudoJet> jets = JetReconstruction(particle_list);

    for(auto j:jets){
        
        std::vector<std::array<int, 2>> i_j;
        if( JetTrigger(j, i_j) ){
            
            for( auto ij: i_j){
                for( int i_had_pt = 0; i_had_pt < hadPtMin.size(); i_had_pt++ ){
                    for( int i_had_rap = 0; i_had_rap < hadRapMin.size(); i_had_rap++ ){
                        
                        GetHist(ij[0],ij[1],i_had_pt,i_had_rap)->JetTriggered();

                    }
                }
            }
        
            SetObservable(j, particle_list, i_j);
            
        
        }
    }

}



std::vector<fjcore::PseudoJet> AnalyzeBase::JetReconstruction( std::vector<std::shared_ptr<Particle>> particle_list ){
    
    std::vector <fjcore::PseudoJet> fj_inputs;
    
    for( auto& p : particle_list ){
        if( p->GetStat() >= 0 ){
            fj_inputs.push_back(p->GetPseudoJet());
        }
    }
    
    fjcore::JetDefinition jetDef =  fjcore::JetDefinition(fjcore::antikt_algorithm, jetR);
    
    fjcore::ClusterSequence clustSeq(fj_inputs, jetDef);
    
    std::vector <fjcore::PseudoJet> jets = sorted_by_pt( clustSeq.inclusive_jets( jetPtCut ) );
    
    jets = sub_ptr->JetSubtraction(jetR, jets, particle_list);

    return jets;
}




void AnalyzeBase::SetLargestRapidity(){
    
    largestRapidity=0.0;
    double rap;
    
    for( int i_jet_rap = 0; i_jet_rap < jetRapMax.size(); i_jet_rap++ ){
        
        rap = jetRapMax[i_jet_rap]+1.2*jetR;
        if( largestRapidity < rap ){
            largestRapidity = rap;
        }
        
    }
    for( int i_had_rap = 0; i_had_rap < hadRapMax.size(); i_had_rap++ ){

        rap = hadRapMax[i_had_rap];
        if( largestRapidity < rap ){
            largestRapidity = rap;
        }

    }
    
    std::cout << "[AnalyzeBase] Largest Rapidity: " << largestRapidity<< std::endl;

}


void AnalyzeBase::SetJetPtCut(){
    
    jetPtCut= 10000.0;
    double pt = 0.0;
    
    for( int i_jet_pt = 0; i_jet_pt < jetPtMin.size(); i_jet_pt++ ){
        
        pt = jetPtMin[i_jet_pt];

        if( jetPtCut > pt ){
            jetPtCut = pt;
        }
        
    }
    
    jetPtCut = 0.6*jetPtCut;
    
    std::cout << "[AnalyzeBase] pt_jet cut: " << jetPtCut << " GeV" << std::endl;

}


bool AnalyzeBase::RapidityCut( std::shared_ptr<Particle> p ){
    
    double rapidity = GetRapidity(p);
    
    if( fabs(rapidity) <= largestRapidity ){
        return true;
    }else{
        return false;
    }
    
}

double AnalyzeBase::GetRapidity( fjcore::PseudoJet j ){
    
    if( hadRapidity == 0){
        return j.rapidity();
    }else{
        return j.eta();
    }
    
}



double AnalyzeBase::GetRapidity( std::shared_ptr<Particle> p ){
    return GetRapidity( p->GetPseudoJet() );
}
