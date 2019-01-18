#include "HistoClass.h"
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

void HistoClass::createHistos()
{
  cout << "There are " << numberOfChannels << " channels." << endl;
  for(int i=0; i<numberOfChannels; i++)
  {
    stringstream SSname; //cout << i << endl;
    TString histoName;// = SSname.str();
    SSname << "ch" << i <<"_scatterHisto";
    histoName = SSname.str(); 
    scatterHisto[i] = new TH2F(histoName,";L.O. (channel);PSP",1000,0,17000,500,0,1);

    //SSname.str("");
    //SSname << "ch" << i <<"_calScatterHisto";
    //histoName = SSname.str(); 
    //cal_scatterHisto[i] = new TH2F(histoName,";time (ns);counts",200,0,200);

    SSname.str("");
    SSname << "ch" << i <<"_energyHisto";
    histoName = SSname.str(); 
    energyHisto[i] = new TH1F(histoName,";L.O. (channel);cpm",16384,0,16384); 

    SSname.str("");
    SSname << "ch" << i <<"_cal_energyHisto";
    histoName = SSname.str(); 
    cal_energyHisto[i] = new TH1F(histoName,";light output (MeVee);counts",10000,0,20);

    SSname.str("");
    SSname << "ch" << i <<"_cal_gammaHisto";
    histoName = SSname.str(); 
    cal_gammaHisto[i] = new TH1F(histoName,";light output (MeVee);counts",10000,0,20);

    SSname.str("");
    SSname << "ch" << i <<"_cal_neutronHisto";
    histoName = SSname.str(); 
    cal_neutronHisto[i] = new TH1F(histoName,";light output (MeVee);counts",10000,0,20);
  }
}

void HistoClass::fillHistos(int channelNumber, double energy, 
                            double psp, TString particleType)
{ 
  if(channelNumber == 4 || channelNumber == 5)
  { 
    //energyHisto[channelNumber]->Fill(energy); //cout << energy << endl;
    //scatterHisto[channelNumber]->Fill(energy, psp);

    if(particleType == "gamma") 
    {
      energyHisto[channelNumber]->Fill(energy); //cout << energy << endl;
      cal_gammaHisto[channelNumber]->Fill(calE);
    }

      scatterHisto[channelNumber]->Fill(energy, psp);

  }
  //cout << "histos filled... " << endl;
  // fill calibrated spectra
  /*if(channelNumber == 1)
  {
    calE =  0.0027 * energy - 0.63;//4.4 / 1880. * energy;
    cal_energyHisto[channelNumber]->Fill(calE);
    if(particleType == "gamma") cal_gammaHisto[channelNumber]->Fill(calE);
    //if(particleType == "neutron") cal_neutronHisto[channelNumber]->Fill(calE);
  }

  if(channelNumber == 2)
  {
    calE =  (0.0017 * energy - 0.088);// * 1.136;
    cal_energyHisto[channelNumber]->Fill(calE);
    if(particleType == "gamma") cal_gammaHisto[channelNumber]->Fill(calE);
    if(particleType == "neutron")
    {
      cal_neutronHisto[channelNumber]->Fill(calE);
    }
    scatterHisto[channelNumber]->Fill(energy, psp);
  }

  if(channelNumber == 3)
  {
    calE =  (0.0016 * energy - 0.72);
    cal_energyHisto[channelNumber]->Fill(calE);
    if(particleType == "gamma") cal_gammaHisto[channelNumber]->Fill(calE);
    //if(particleType == "neutron")
    //{
      cal_neutronHisto[channelNumber]->Fill(calE);
      scatterHisto[channelNumber]->Fill(energy, psp);
    //}
  }*/
}

void HistoClass::normalizeHistos(double time)
{
  for(int i=0; i<numberOfChannels; i++)
  { 
    //scatterHisto[i]->Write();
    energyHisto[i]->Scale(1/time);
    scatterHisto[i]->Scale(1/time);
    //gammaCut[i]->Write();
  }
}

void HistoClass::createAndWriteRootFile(TString outFileName)
{
  cout << "writing ROOT file... " << endl;
  stringstream ss;
  ss << "_processed.root";
  TString name = ss.str();

  TFile *run = new TFile(outFileName,"recreate");
	run->SetCompressionSettings(3);

  for(int i=0; i<numberOfChannels; i++)
  //for(int i=3; i<5; i++)
  { 
    //scatterHisto[i]->Write();
    //energyHisto[i]->Write();
    //cal_energyHisto[i]->Write();
    //scatterHisto[i]->Write();
    //gammaCut[i]->Write();
    //neutronCut[i]->Write();

    //if(i==3) scatterHisto[i]->Write();

    if(i==4 || i==5)// || i==4) 
    {
      scatterHisto[i]->Write();
      energyHisto[i]->Write();
      //cal_neutronHisto[i]->Write();
      //cal_gammaHisto[i]->Write();
      //gammaCut[i]->Write();
      //neutronCut[i]->Write();
    }
  }
  
  //cout << "write the rate histos... " << endl;  

  /*int numOfBins = rateVal.size();
  for(int i=0; i<numberOfChannels; i++)
  {  
    stringstream SSname; //cout << i << endl;
    TString histoName;// = SSname.str();
    SSname << "ch" << i <<"_rateHisto";
    histoName = SSname.str(); 
        
    rateHisto[i] = new TH1F(histoName,";File Number;rate",numOfBins,0,numOfBins);
  }
  
  for(int i=0; i<numOfBins; i++)
  {
    rateHisto[2]->SetBinContent(i+1,rateVal.at(i));
    cout << rateVal.at(i) << endl;
  }
  rateHisto[2]->Write();*/
  run->Close();  
}

