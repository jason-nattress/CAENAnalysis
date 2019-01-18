#include "WaveClass.h"
//#include "constants.h"
//#include "analyze.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

//Root headers
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TCutG.h>

//void WaveClass::createHistos()
//{}

void WaveClass::openBinaryFile(string inputFileName)
{
  inFile.open(inputFileName.c_str(), ios::binary|ios::in);
  if(!inFile.good()) cout << "file is not open" << '\n'; //check file is open

  totalEventCounter = 0;
}

void WaveClass::closeFile()
{
  inFile.close();
}

void WaveClass::createWaveHistos()
{
  for(int i=0; i<100; i++)
  {
    stringstream SSname; //cout << i << endl;
    TString histoName;// = SSname.str();
    SSname << "wave_" << i;
    histoName = SSname.str(); 
    waveHisto[i] = new TH1F(histoName,";sample (4 ns);channel",496,0,496);
  }
}

void WaveClass::writeToFile()
{
  TFile *run = new TFile("waves.root","recreate");
	run->SetCompressionSettings(3);

  for(int i=0; i<100; i++)
  {
    waveHisto[i]->SetLineColor(i);
    waveHisto[i]->Write();
  }

  run->Close();  
}


bool WaveClass::readWave() 
//check manual for what headers mean if you would like to use them.... 
{
  currentWave.clear();
  
  if (!inFile) 
  {
    cout << "An error occurred!" << '\n';
  }

  inFile.read((char*)&board,sizeof(int16_t));
  inFile.read((char*)&channel,sizeof(int16_t)); 
  inFile.read((char*)&timestamp,sizeof(int64_t)); 
  inFile.read((char*)&energy,sizeof(int16_t));
  inFile.read((char*)&shortEnergy,sizeof(int16_t));  
  inFile.read((char*)&flags,sizeof(int16_t));  
  inFile.read((char*)&numberOfWaveSamplesToBeRead,sizeof(int32_t));  

  if(totalEventCounter==0)
  {
    cout << board << endl;
    cout << endl << "event" << endl;
    cout << "board: " << board << endl;
    cout << "ch: " << channel << endl;
    cout << "ts: " << timestamp << endl;
    cout << "E: " << energy << endl;
    cout << "sE: " << shortEnergy << endl;
    cout << numberOfWaveSamplesToBeRead << endl;
  }
  
  int16_t sample;
  
  for(int i=0;i<numberOfWaveSamplesToBeRead;i++)
  {
    inFile.read((char*)&sample,sizeof(int16_t));
    currentWave.push_back(sample);
    //cout << i << ": " <<  sample << " " << endl;
  }

  bool checkFile;
  checkFile = inFile.eof();

  if(totalEventCounter<100)
  {
    for(int i=0;i<currentWave.size();i++)
    { //cout << i << " " << currentWave.at(i) << endl;
      waveHisto[totalEventCounter]->SetBinContent(i,currentWave.at(i));
    }
  }

  totalEventCounter++;
  
  return checkFile;
}

void WaveClass::calculatePulseInfo()        
{
  psp = (energy - shortEnergy) / energy;
}

















