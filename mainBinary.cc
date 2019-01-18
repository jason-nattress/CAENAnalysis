// Programmer: Jason Nattress
// Purpose:
// Date: 2/3/2018
// Compliation command: 
// g++ mainBinary.cc HistoClass.cc analyze.cc WaveClass.cc `root-config --libs --cflags` -o main -O3 -ftree-vectorize
// Execution command: ./main/path/to/file/without/file/number
/////////////////////////////////////////////////////////
#include "analyze.h"
#include "HistoClass.h"
#include "WaveClass.h"
//#include <TH2.h>
//#include <TStyle.h>
//#include <TCanvas.h>
//#include <TCutG.h>

int main(int argc, char** argv)
{ 
  // Read in final ROOT file and grab energy calibration
  cout << "What is you outFile name?" << endl;
  TString outFileName;
  cin >> outFileName;

  HistoClass histos;
  histos.createHistos();

  cout<<"Starting to perform analysis"<<endl;

  WaveClass waveforms; 
  
  string inputFileName = argv[1];
 
  waveforms.openBinaryFile(inputFileName);
  waveforms.createWaveHistos();
  
  bool endOfFile = false;
  while(!endOfFile)
  //while(waveforms.totalEventCounter<2)
  {
    endOfFile = waveforms.readWave();
  }

  cout << waveforms.totalEventCounter << endl;

  waveforms.writeToFile();

  waveforms.closeFile();

  //histos.normalizeHistos(time);
  //histos.createAndWriteRootFile(outFileName);
       
  return 0; 
}
