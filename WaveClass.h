//Programmer: Jason Nattress
//Purpose: 
#ifndef _WAVECLASS_H_
#define _WAVECLASS_H_

#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <vector>
#include <fstream>

#include "constants.h"

using namespace std;

class WaveClass
{
  private:
    ifstream inFile;

    int16_t board;
    int16_t channel;
    int64_t timestamp; 
    int16_t energy;
    int16_t shortEnergy;
    int16_t flags;
    int32_t numberOfWaveSamplesToBeRead; //record length in samples

    double longGate, shortGate, baseline, psp;

    TH1F *waveHisto[100]; //used quick to look at waves
    TH1F *energyHisto[numberOfChannels]; 
    TH2F *scatterHisto[numberOfChannels];
       
  public:
    void openBinaryFile(string inputFileName); //opens file
    bool readWave(int recordLength); //reads in one wave and store it in a vector 
    void closeFile();
    void createWaveHistos(); //just writes the first 100 waves into TH1F
    void writeToFile(); //write waves to file

    int totalEventCounter; //total number of events
    vector<double> currentWave; //vector of current wave

    void calculatePulseInfo();
    void fillHistos();
};

#endif 





