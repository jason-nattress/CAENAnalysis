//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb  2 00:11:29 2018 by ROOT version 6.06/06
// from TTree Data/CoMPaSS TTree with sorted events
// found on file: compass_run_1_525.root
//////////////////////////////////////////////////////////
//Programmer: Jason Nattress
//Purpose:
//Date: 2/3/2018

#ifndef analyze_h
#define analyze_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TCutG.h>

#include "HistoClass.h"

using namespace std;

// Header file for the classes stored in the TTree if any.

class analyze 
{
  private :
    TCutG *gammaCut[numberOfChannels];
    TCutG *neutronCut[numberOfChannels];

  public :
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain

    // my variables
    double totalTime;
    double selectedCounts;
    
    // Fixed size dimensions of array or collections stored in the TTree if any.

    // Declaration of leaf types
    UShort_t        Channel;
    ULong64_t       Timestamp;
    UShort_t        Board;
    UShort_t        Energy;
    UShort_t        EnergyShort;
    UInt_t          Flags;

    // List of branches
    TBranch        *b_Channel;   //!
    TBranch        *b_Timestamp;   //!
    TBranch        *b_Board;   //!
    TBranch        *b_Energy;   //!
    TBranch        *b_EnergyShort;   //!
    TBranch        *b_Flags;   //!

    analyze(string filename, TTree *tree=0);
    virtual ~analyze();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop(string fileName, HistoClass histos);
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
    
    double calculateEventRate(int minuteCounter); 
    void MakeCuts();
    void writeCuts();
};

#endif

//#ifdef analyze_cxx

//#endif // #ifdef analyze_cxx
