#ifndef AnalyzeBase_H_
#define AnalyzeBase_H_

#include "Histogram.h"
#include "LoadFileBase.h"
#include "LoadJetScapeAscii.h"
#include "Pythia8/Pythia.h"
#include "../fjcore/fjcore.hh"
#include "SubtractionBase.h"
#include "SubNegatives.h"

#include <iostream>
#include <cfloat>
#include <vector>
#include <array>

class AnalyzeBase{
public:
    
    int test_tag;
    
    virtual ~AnalyzeBase();
    void Init();
    void Analyze(std::string input_file_name);
    void Start(double ptHatMin, double ptHatMax);
    void End();
    
    long getMemoryUsage();
    
protected:
    
    double jetR;
    
    std::vector<double> jetRapMin;
    std::vector<double> jetRapMax;
    std::vector<double> jetPtMin;
    std::vector<double> jetPtMax;
    
    std::vector<double> hadRapMin;
    std::vector<double> hadRapMax;
    std::vector<double> hadPtMin;
    std::vector<double> hadPtMax;
    
    bool HadTrigger(std::shared_ptr<Particle> p, std::vector<std::array<int, 2>> &i_h );
    std::shared_ptr<Histogram> GetHist(int i_jet_pt, int i_jet_rap, int i_had_pt, int i_had_rap);
    std::unique_ptr<SubtractionBase> sub_ptr;

    
private:
    
    virtual void SetObservable(fjcore::PseudoJet jet, std::vector<std::shared_ptr<Particle>> particle_list, std::vector<std::array<int, 2>> i_j ){}
    
    void EventEndMark(std::vector<std::shared_ptr<Particle>> &particle_list, int &event_num);
    virtual void OneEventAnalysis(std::vector<std::shared_ptr<Particle>> particle_list);
    
    std::vector<fjcore::PseudoJet> JetReconstruction( std::vector<std::shared_ptr<Particle>> particle_list );
    
    bool RapidityCut( std::shared_ptr<Particle> p );
    
    void InitSettings();
    
    void SetLargestRapidity();
    void SetJetPtCut();
    
    void GenerateHist(double ptHatMin, double ptHatMax);
    void InitHist();
    void DeleteHist();
    
    bool JetTrigger(fjcore::PseudoJet jets, std::vector<std::array<int, 2>> &i_j );

    
    double GetRapidity( std::shared_ptr<Particle> p );
    double GetRapidity( fjcore::PseudoJet j );
    
    
    
    std::string GetHistName(double ptHatMin, double ptHatMax, int i_jet_pt, int i_jet_rap, int i_had_pt, int i_had_rap);
    
    std::string JetType(int chJet);
    std::string HadronType(int chHad);
    std::string RapType(int rap);
    
    virtual std::string ObservableName();
    std::vector<std::shared_ptr<Histogram>> hist_list;
    
    

    
    
    int chJet;
    //    double primHadPtMin;
    //    int chPrimHad;
    int jetRapidity;
    
    int chHad;
    int hadRapidity;
    
    double largestRapidity;
    double jetPtCut; 
    
    std::string inputStyle;
    std::string subMethod;
    
    double chMin;
    Pythia8::Pythia pythia;
    
    
    
};

#endif 
