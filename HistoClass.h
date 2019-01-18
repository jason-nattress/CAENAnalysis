//Programmer: Jason Nattress
//Purpose: 
#ifndef _HISTOCLASS_H_
#define _HISTOCLASS_H_

#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <vector>

#include "include/constants.h"
//#include "analyze.h"
//const int numberOfChannels = 8;

using namespace std;

class HistoClass
{
  private:
    

  public:
    TH2F *scatterHisto[numberOfChannels];
    TH2F *cal_scatterHisto[numberOfChannels];
    TH1F *energyHisto[numberOfChannels]; 
    TH1F *cal_energyHisto[numberOfChannels];
    TH1F *cal_neutronHisto[numberOfChannels];
    TH1F *cal_gammaHisto[numberOfChannels];
    TH1F *rateHisto[numberOfChannels];
    //TH1F *waveHisto[numberOfChannels];

    double calE;
    vector<double> rateVal;

    //void fillRateVector();
    void createHistos();
    void fillHistos(int channelNumber, double energy, 
                    double psp, TString particleType);
    void normalizeHistos(double time);
    void createAndWriteRootFile(TString outFileName);
    void writeCuts();
};

#endif 





