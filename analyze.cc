//Programmer: Jason Nattress
//Purpose:
//Date: 2/3/2018
// g++ analyze.cpp `root-config --libs --cflags` -o a -O3
#define analyze_cxx
#include "analyze.h"
#include "HistoClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TCutG.h>

using namespace std;

void analyze::Loop(string fileName, HistoClass histos)
{
  if (fChain == 0) return;
  selectedCounts = 0;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  //cout << "f" << endl;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) 
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;

    bool keepOn = false;

    // channels 4&5 are the NaI detectors
    if(Channel == 4 || Channel == 5)
    {
      double energy = Energy;
      double psp;
      TString particleType;

      if( Energy > EnergyShort) 
      {
        psp = (energy - EnergyShort) / energy;
        //cout << psp << endl;
        keepOn = true;
      }
      if(keepOn) //cout << Channel << endl;
      //cout << Energy << " " << EnergyShort << endl;
      {
        //if(gammaCut[Channel]->IsInside(energy,psp)) particleType = "gamma";

        //
        //particleType = "none";

        if(Channel == 4)// || Channel == 3) 
        {
          //if(neutronCut[Channel]->IsInside(energy,psp)) particleType = "neutron";
          if(gammaCut[Channel]->IsInside(energy,psp)) particleType = "gamma";
          
          
          double val =  (0.0017 * energy - 0.088);//cout << val << endl;
          if(val > .200) selectedCounts++; 
        }

        else if(Channel == 5)// || Channel == 3) 
        {
          //if(neutronCut[Channel]->IsInside(energy,psp)) particleType = "neutron";
          if(gammaCut[Channel]->IsInside(energy,psp)) particleType = "gamma";
        }

        else {particleType = "none";}
        //cout << Channel << " " << " " << energy << " " << psp << " " 
        //     << particleType << " " << endl;
        // calibration is performed in fillHistos member
        // this probably isn't the best spot for it
        histos.fillHistos(Channel,energy,psp,particleType);         
      }
    }
  }
  
  totalTime = Timestamp / 1.E12;
  cout << "sc: " << selectedCounts << endl;  
  cout << "time: " << totalTime << endl;
}

void analyze::MakeCuts()
{
  // make cuts
  /*gammaCut[1] = new TCutG("ch1_gammaCut",23);
  gammaCut[1]->SetVarX("");
  gammaCut[1]->SetVarY("");
  gammaCut[1]->SetTitle("ch1_gCut");
  gammaCut[1]->SetFillColor(1);
  gammaCut[1]->SetPoint(0,116.244,0.0980047);
  gammaCut[1]->SetPoint(1,202.809,0.381162);
  gammaCut[1]->SetPoint(2,351.205,0.492664);
  gammaCut[1]->SetPoint(3,524.335,0.529343);
  gammaCut[1]->SetPoint(4,957.159,0.568955);
  gammaCut[1]->SetPoint(5,1711.51,0.596831);
  gammaCut[1]->SetPoint(6,2540.06,0.610035);
  gammaCut[1]->SetPoint(7,3838.53,0.627641);
  gammaCut[1]->SetPoint(8,3838.53,0.627641);
  gammaCut[1]->SetPoint(9,5470.89,0.634977);
  gammaCut[1]->SetPoint(10,7449.52,0.649648);
  gammaCut[1]->SetPoint(11,8142.03,0.649648);
  gammaCut[1]->SetPoint(12,8154.4,0.690728);
  gammaCut[1]->SetPoint(13,5903.72,0.668721);
  gammaCut[1]->SetPoint(14,4407.38,0.658451);
  gammaCut[1]->SetPoint(15,2873.95,0.640845);
  gammaCut[1]->SetPoint(16,1699.14,0.632042);
  gammaCut[1]->SetPoint(17,784.029,0.615904);
  gammaCut[1]->SetPoint(18,165.71,0.574824);
  gammaCut[1]->SetPoint(19,91.5112,0.52054);
  gammaCut[1]->SetPoint(20,29.6792,0.0818662);
  gammaCut[1]->SetPoint(21,103.878,0.0994718);
  gammaCut[1]->SetPoint(22,116.244,0.0980047);

  gammaCut[2] = new TCutG("ch2_gammaCut",17);
  gammaCut[2]->SetVarX("");
  gammaCut[2]->SetVarY("");
  gammaCut[2]->SetTitle("ch1gCut");
  gammaCut[2]->SetFillColor(1);
  gammaCut[2]->SetPoint(0,142.139,0.120849);
  gammaCut[2]->SetPoint(1,2345.67,0.117019);
  gammaCut[2]->SetPoint(2,4270.36,0.118168);
  gammaCut[2]->SetPoint(3,8888.26,0.122765);
  gammaCut[2]->SetPoint(4,8901.86,0.102463);
  gammaCut[2]->SetPoint(5,5351.73,0.0959518);
  gammaCut[2]->SetPoint(6,3875.9,0.0909722);
  gammaCut[2]->SetPoint(7,2746.93,0.0859927);
  gammaCut[2]->SetPoint(8,1658.77,0.0783319);
  gammaCut[2]->SetPoint(9,958.262,0.0641594);
  gammaCut[2]->SetPoint(10,631.813,0.051902);
  gammaCut[2]->SetPoint(11,461.787,0.0346652);
  gammaCut[2]->SetPoint(12,312.164,0.0132149);
  gammaCut[2]->SetPoint(13,6.11829,0.0120658);
  gammaCut[2]->SetPoint(14,33.3224,0.121232);
  gammaCut[2]->SetPoint(15,182.945,0.121232);
  gammaCut[2]->SetPoint(16,142.139,0.120849);

  neutronCut[2] = new TCutG("ch2_neutronCut",17);
  neutronCut[2] ->SetVarX("");
  neutronCut[2] ->SetVarY("");
  neutronCut[2] ->SetTitle("Graph");
  neutronCut[2] ->SetFillColor(1);
  neutronCut[2]->SetPoint(0,69.2934,0.24587);
  neutronCut[2]->SetPoint(1,441.425,0.24587);
  neutronCut[2]->SetPoint(2,762.228,0.232054);
  neutronCut[2]->SetPoint(3,1468,0.209539);
  neutronCut[2]->SetPoint(4,2122.43,0.189583);
  neutronCut[2]->SetPoint(5,3046.35,0.176791);
  neutronCut[2]->SetPoint(6,3752.11,0.168092);
  neutronCut[2]->SetPoint(7,4778.68,0.162975);
  neutronCut[2]->SetPoint(8,5522.95,0.160417);
  neutronCut[2]->SetPoint(9,6665.01,0.159393);
  neutronCut[2]->SetPoint(10,7858.39,0.159393);
  neutronCut[2]->SetPoint(11,13068.2,0.159393);
  neutronCut[2]->SetPoint(12,13068.2,0.141484);
  neutronCut[2]->SetPoint(13,7062.8,0.13125);
  neutronCut[2]->SetPoint(14,56.4612,0.130227);
  neutronCut[2]->SetPoint(15,43.6291,0.245358);
  neutronCut[2]->SetPoint(16,69.2934,0.24587);

  neutronCut[3] = new TCutG("ch3_neutronCut",14);
  neutronCut[3]->SetVarX("");
  neutronCut[3]->SetVarY("");
  neutronCut[3]->SetTitle("Graph");
  neutronCut[3]->SetFillColor(1);
  neutronCut[3]->SetPoint(0,56.4612,0.160417);
  neutronCut[3]->SetPoint(1,6742,0.153083);
  neutronCut[3]->SetPoint(2,8025.21,0.156139);
  neutronCut[3]->SetPoint(3,9346.92,0.162861);
  neutronCut[3]->SetPoint(4,9603.56,0.183028);
  neutronCut[3]->SetPoint(5,5471.62,0.181806);
  neutronCut[3]->SetPoint(6,3007.85,0.188528);
  neutronCut[3]->SetPoint(7,1929.95,0.20075);
  neutronCut[3]->SetPoint(8,1134.36,0.216639);
  neutronCut[3]->SetPoint(9,595.411,0.241694);
  neutronCut[3]->SetPoint(10,43.6291,0.277139);
  neutronCut[3]->SetPoint(11,17.9648,0.161028);
  neutronCut[3]->SetPoint(12,364.432,0.160417);
  neutronCut[3]->SetPoint(13,56.4612,0.160417);

  gammaCut[3] = new TCutG("ch3_gammaCut",13);
  gammaCut[3]->SetVarX("");
  gammaCut[3]->SetVarY("");
  gammaCut[3]->SetTitle("Graph");
  gammaCut[3]->SetFillColor(1);
  gammaCut[3]->SetPoint(0,30.797,0.160148);
  gammaCut[3]->SetPoint(1,787.892,0.149256);
  gammaCut[3]->SetPoint(2,2327.75,0.143156);
  gammaCut[3]->SetPoint(3,9590.73,0.156227);
  gammaCut[3]->SetPoint(4,10027,0.157098);
  gammaCut[3]->SetPoint(5,9911.53,0.1388);
  gammaCut[3]->SetPoint(6,1981.28,0.100025);
  gammaCut[3]->SetPoint(7,1249.85,0.0943611);
  gammaCut[3]->SetPoint(8,685.235,0.0799839);
  gammaCut[3]->SetPoint(9,441.425,0.063864);
  gammaCut[3]->SetPoint(10,56.4612,0.0446944);
  gammaCut[3]->SetPoint(11,69.2934,0.157534);
  gammaCut[3]->SetPoint(12,30.797,0.160148);

  */
  // ch4
  gammaCut[4] = new TCutG("ch4_gammaCut",15);
  gammaCut[4]->SetVarX("");
  gammaCut[4]->SetVarY("");
  gammaCut[4]->SetTitle("Graph");
  gammaCut[4]->SetFillStyle(1000);
  gammaCut[4]->SetLineWidth(2);
  gammaCut[4]->SetPoint(0,141.286,0.504659);
  gammaCut[4]->SetPoint(1,296.546,0.817708);
  gammaCut[4]->SetPoint(2,1150.47,0.844493);
  gammaCut[4]->SetPoint(3,2982.54,0.854537);
  gammaCut[4]->SetPoint(4,16008.8,0.882996);
  gammaCut[4]->SetPoint(5,16676.4,0.883833);
  gammaCut[4]->SetPoint(6,16645.4,0.861233);
  gammaCut[4]->SetPoint(7,4302.24,0.833611);
  gammaCut[4]->SetPoint(8,2128.61,0.826078);
  gammaCut[4]->SetPoint(9,1181.53,0.811849);
  gammaCut[4]->SetPoint(10,607.065,0.76916);
  gammaCut[4]->SetPoint(11,358.65,0.502985);
  gammaCut[4]->SetPoint(12,110.234,0.503822);
  gammaCut[4]->SetPoint(13,110.234,0.503822);
  gammaCut[4]->SetPoint(14,141.286,0.504659);

  gammaCut[5] = new TCutG("ch5_gammaCut",23);
  gammaCut[5]->SetVarX("");
  gammaCut[5]->SetVarY("");
  gammaCut[5]->SetTitle("Graph");
  gammaCut[5]->SetFillStyle(1000);
  gammaCut[5]->SetLineWidth(2);
  gammaCut[5]->SetPoint(0,469.995,0.562769);
  gammaCut[5]->SetPoint(1,727.829,0.65778);
  gammaCut[5]->SetPoint(2,779.396,0.69461);
  gammaCut[5]->SetPoint(3,801.496,0.730373);
  gammaCut[5]->SetPoint(4,849.38,0.762932);
  gammaCut[5]->SetPoint(5,1000.4,0.795492);
  gammaCut[5]->SetPoint(6,1206.66,0.814708);
  gammaCut[5]->SetPoint(7,1950.7,0.840862);
  gammaCut[5]->SetPoint(8,2764.72,0.851538);
  gammaCut[5]->SetPoint(9,5726.13,0.87022);
  gammaCut[5]->SetPoint(10,5718.76,0.887834);
  gammaCut[5]->SetPoint(11,3446.14,0.880361);
  gammaCut[5]->SetPoint(12,2654.22,0.873422);
  gammaCut[5]->SetPoint(13,1737.07,0.861146);
  gammaCut[5]->SetPoint(14,1077.75,0.83766);
  gammaCut[5]->SetPoint(15,864.113,0.823248);
  gammaCut[5]->SetPoint(16,690.996,0.796026);
  gammaCut[5]->SetPoint(17,554.712,0.757061);
  gammaCut[5]->SetPoint(18,539.978,0.709022);
  gammaCut[5]->SetPoint(19,381.595,0.546756);
  gammaCut[5]->SetPoint(20,352.128,0.524338);
  gammaCut[5]->SetPoint(21,473.678,0.562769);
  gammaCut[5]->SetPoint(22,469.995,0.562769);
}

analyze::analyze(string filename, TTree *tree) : fChain(0) 
{
	char cname[256];
	cout << "file name is: " << filename << endl;
	strncpy(cname, filename.c_str(), sizeof(cname));
	cname[sizeof(cname) - 1] = 0;
		
  if (tree == 0) 
  {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(cname);
    if (!f || !f->IsOpen()) 
    {
      f = new TFile(cname);
    }
    f->GetObject("Data",tree);
  }

  Init(tree);
}

analyze::~analyze()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t analyze::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t analyze::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void analyze::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Channel", &Channel, &b_Channel);
   fChain->SetBranchAddress("Timestamp", &Timestamp, &b_Timestamp);
   fChain->SetBranchAddress("Board", &Board, &b_Board);
   fChain->SetBranchAddress("Energy", &Energy, &b_Energy);
   fChain->SetBranchAddress("EnergyShort", &EnergyShort, &b_EnergyShort);
   fChain->SetBranchAddress("Flags", &Flags, &b_Flags);
   Notify();
}

Bool_t analyze::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void analyze::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t analyze::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void analyze::writeCuts()
{
  TFile *run = new TFile("cuts.root","recreate");
	run->SetCompressionSettings(3);

  for(int i=0; i<numberOfChannels; i++)
  //for(int i=3; i<5; i++)
  { 

    if(i==4 || i==5) 
    {
      gammaCut[i]->Write();
      //neutronCut[i]->Write();
    }
  }

  run->Close();  
}

double analyze::calculateEventRate(int minuteCounter)
{
  if(Timestamp % 60 > minuteCounter)
  {
    cout << Timestamp << " minute ";
  } 
}

















