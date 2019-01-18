// Programmer: Jason Nattress
// Purpose:
// Date: 2/3/2018
// Compliation command: 
// g++ main.cc HistoClass.cc analyze.cc `root-config --libs --cflags` -o main -O3 -ftree-vectorize
// Execution command: ./main /path/to/file/without/file/number
/////////////////////////////////////////////////////////
#include "analyze.h"
#include "HistoClass.h"
//#include <TH2.h>
//#include <TStyle.h>
//#include <TCanvas.h>
//#include <TCutG.h>

int main(int argc, char** argv)
{ 
  // Read in final ROOT file and grab energy calibration
   
  cout << "How many files are you going to process?" << endl;
  int numOfFilesToProcess;
  cin >> numOfFilesToProcess;
  
  cout << "What is you outFile name?" << endl;
  TString outFileName;
  cin >> outFileName;

  HistoClass histos;
  histos.createHistos();

  cout<<"Starting to perform analysis"<<endl;

  double time = 0;
  double prevTime = 0;

  for(int fileNum=1; fileNum < numOfFilesToProcess; fileNum++) //705
  {
  //if(time < 7200)
  //{
    stringstream ss;
    // run 6 for the Feb1
    // run 10 for Feb 3
    ss << argv[1] << fileNum << ".root";
    string fileName = ss.str();

    analyze data(fileName);
    data.MakeCuts();

    data.Loop(fileName, histos);
    time = data.totalTime;
    
    double val = data.selectedCounts / (data.totalTime-prevTime);

    prevTime = time;
    
    histos.rateVal.push_back(val);
    
    if(fileNum == 1)   data.writeCuts();

  //}    
  } 
  cout << "you're done... " << endl;
  //histos.normalizeHistos(time);
  histos.createAndWriteRootFile(outFileName);
       
  return 0; 
}
