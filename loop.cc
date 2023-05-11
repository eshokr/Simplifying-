// To loop over a tree branches and combare different branches from different trees this code can be used
// Eslam Shokr
// 11-5-2023

// one have to do: 
// 1- root -l file.root
// 2- tree_name ->MakeClass("tree")
// This will create tree.h and tree.C files that will be used for this code 

// .L loop.C++

#include <vector>
#include <iostream>
#include <string>
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include <TStyle.h>
#include "TROOT.h"
#include <map>
#include "TLegend.h"
#include "TColor.h"
#include "TFile.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TLorentzVector.h"
#include "TGraphAsymmErrors.h"
#include "TLatex.h"
#include "TBranch.h"
#include "TTree.h"
#include "TChain.h"
#include "TMinuit.h"
#include "TProfile.h"
#include "TLine.h"
#include "TPaveStats.h"

#include "tree.C"

using namespace std;

void setCanvasProperties(TCanvas* canvas) {
    canvas->SetGrid();
  //  canvas->SetLogy();
    canvas->SetLeftMargin(0.12);
}


TH1F* createHistogram(const char* name, const char* title, int nbins, double xmin, double xmax,
                      Color_t lineColor = kBlack, Width_t lineWidth = 1,
                      const char* xTitle = "", const char* yTitle = "", Size_t xTitleSize = 0, Size_t yTitleSize = 0,
                      Size_t markerSize = 1.0, Color_t markerColor = kBlack, Color_t fillColor = 0, Style_t fillStyle = 0)
{
    TH1F* histogram = new TH1F(name, title, nbins, xmin, xmax);
    
    histogram->GetYaxis()->SetTitleSize(0.04);

    histogram->GetYaxis()->SetLabelSize(0.04);
    
    histogram->SetLineColor(lineColor);
    histogram->SetLineWidth(lineWidth);
    if (strlen(xTitle) > 0) {
        histogram->GetXaxis()->SetTitle(xTitle);
    }
    if (strlen(yTitle) > 0) {
        histogram->GetYaxis()->SetTitle(yTitle);
    }
    if (xTitleSize > 0) {
        histogram->GetXaxis()->SetTitleSize(xTitleSize);
    }
    if (yTitleSize > 0) {
        histogram->GetYaxis()->SetTitleSize(yTitleSize);
    }
    histogram->SetMarkerSize(markerSize);
    histogram->SetMarkerColor(markerColor);
    if (fillColor > 0) {
        histogram->SetFillColor(fillColor);
    }
    if (fillStyle > 0) {
        histogram->SetFillStyle(fillStyle);
    }
    histogram->SetStats(false);
    return histogram;
}


void loop(){

    double CROSSSECTION_A01= 1.4329;
    double CROSSSECTION_A0=  1.0647;
    double CROSSSECTION_A_01= 0.856;
    
    double muonPionEtaCut= 2.5;
    double muonPtCut= 2.5;
    double pionPtCut= 0.3;
    
   // TFile * f1 = new TFile(file.c_str(),"READ");
    auto f1 = TFile::Open("tree01.root");
    auto f2 = TFile::Open("tree0.root");
    auto f3 = TFile::Open("tree-01.root");

    if (!f1 || f1->IsZombie() ||!f2 || f2->IsZombie()||!f3 || f3->IsZombie() ) {
        std::cerr << "Error: unable to open file '*.root'\n";
        return;
    }

    tree * t1 = new tree((TTree*)f1->Get("Muon3Pions"));
    tree * t2 = new tree((TTree*)f2->Get("Muon3Pions"));
    tree * t3 = new tree((TTree*)f3->Get("Muon3Pions"));

    if (!t1 ||!t2 ||!t3 ) {
        std::cerr << "Error: unable to get TTree object from file\n";
        return;
    }
    
    // Create the histograms from the tree branches and set their properties
    TH1F* hPt1 = createHistogram("hPt1", "", 100, 0, 20, kRed, 3, "Muon p_{T} (GeV/c)", "No. of Entries/bin * Cross Section", 0.05, 0.05);
    TH1F* hPt2 = createHistogram("hPt2", "", 100, 0, 20, kBlack, 2, "Muon p_{T} (GeV/c)", "No. of Entries/bin", 0.05, 0.05);
    TH1F* hPt3 = createHistogram("hPt3", "", 100, 0, 20, kGreen, 1, "Muon p_{T} (GeV/c)", "No. of Entries/bin", 0.05, 0.05);
    
    
    //the TH1::Sumw2 called before filling, to store the sum of squares of weights.
    hPt1->Sumw2();
    hPt2->Sumw2();
    hPt3->Sumw2();

  // find the events with candidates
  int entries_t1 = (t1->fChain)->GetEntries();
  
    //  for (int i = 0; i < 100 ; i++){
        for(int iEntry=0; iEntry<entries_t1; iEntry++) {
            (t1->fChain)->GetEntry(iEntry);
            
     //       if(iEntry%200==0)
      //          cout << "\r" << (double)iEntry/(double)entries_t3*100 << "\% processed" << flush;

            // Declaration of leaf types
            double muon3Pions_Muon_Pt_t1 = t1->muon3Pions_Muon_Pt;
            double muon3Pions_Muon_Eta_t1 = t1->muon3Pions_Muon_Eta;
            double muon3Pions_Pion1_Pt_t1 = t1->muon3Pions_Pion1_Pt;
            double muon3Pions_Pion1_Eta_t1 = t1->muon3Pions_Pion1_Eta;
            double muon3Pions_Pion2_Pt_t1 = t1->muon3Pions_Pion2_Pt;
            double muon3Pions_Pion2_Eta_t1 = t1->muon3Pions_Pion2_Pt;
            double muon3Pions_Pion3_Pt_t1 = t1->muon3Pions_Pion3_Pt;
            double muon3Pions_Pion3_Eta_t1 = t1->muon3Pions_Pion3_Pt;
            
            if (muon3Pions_Muon_Pt_t1>muonPtCut && fabs(muon3Pions_Muon_Eta_t1)<muonPionEtaCut&& muon3Pions_Pion1_Pt_t1>pionPtCut && muon3Pions_Pion2_Pt_t1>pionPtCut && muon3Pions_Pion3_Pt_t1>pionPtCut &&  fabs(muon3Pions_Pion1_Eta_t1)<muonPionEtaCut &&  fabs(muon3Pions_Pion2_Eta_t1)<muonPionEtaCut &&  fabs(muon3Pions_Pion3_Eta_t1)<muonPionEtaCut){
                hPt1->Fill(muon3Pions_Muon_Pt_t1);
            }
        } // end of the for loop on events

    // find the events with candidates
     int entries_t2 = (t2->fChain)->GetEntries();
   // for (int i = 0; i < 100 ; i++){
        
        for(int iEntry=0; iEntry<entries_t2; iEntry++) {
            (t2->fChain)->GetEntry(iEntry);
  
            
            // Declaration of leaf types
            double muon3Pions_Muon_Pt_t2 = t2->muon3Pions_Muon_Pt;
            double muon3Pions_Muon_Eta_t2 = t2->muon3Pions_Muon_Eta;
            double muon3Pions_Pion1_Pt_t2 = t2->muon3Pions_Pion1_Pt;
            double muon3Pions_Pion1_Eta_t2 = t2->muon3Pions_Pion1_Eta;
            double muon3Pions_Pion2_Pt_t2 = t2->muon3Pions_Pion2_Pt;
            double muon3Pions_Pion2_Eta_t2 = t2->muon3Pions_Pion2_Pt;
            double muon3Pions_Pion3_Pt_t2 = t2->muon3Pions_Pion3_Pt;
            double muon3Pions_Pion3_Eta_t2 = t2->muon3Pions_Pion3_Pt;
            
            if (muon3Pions_Muon_Pt_t2>muonPtCut && fabs(muon3Pions_Muon_Eta_t2)<muonPionEtaCut&& muon3Pions_Pion1_Pt_t2>pionPtCut && muon3Pions_Pion2_Pt_t2>pionPtCut && muon3Pions_Pion3_Pt_t2>pionPtCut &&  fabs(muon3Pions_Pion1_Eta_t2)<muonPionEtaCut &&  fabs(muon3Pions_Pion2_Eta_t2)<muonPionEtaCut &&  fabs(muon3Pions_Pion3_Eta_t2)<muonPionEtaCut){
                hPt2->Fill(muon3Pions_Muon_Pt_t2);
                
            }
        } // end of the for loop on events

    // find the events with candidates
    int entries_t3 = (t3->fChain)->GetEntries();
          for(int iEntry=0; iEntry<entries_t3; iEntry++) {
            (t3->fChain)->GetEntry(iEntry);

            // Declaration of leaf types
            double muon3Pions_Muon_Pt_t3 = t3->muon3Pions_Muon_Pt;
            double muon3Pions_Muon_Eta_t3 = t3->muon3Pions_Muon_Eta;
            double muon3Pions_Pion1_Pt_t3 = t3->muon3Pions_Pion1_Pt;
            double muon3Pions_Pion1_Eta_t3 = t3->muon3Pions_Pion1_Eta;
            double muon3Pions_Pion2_Pt_t3 = t3->muon3Pions_Pion2_Pt;
            double muon3Pions_Pion2_Eta_t3 = t3->muon3Pions_Pion2_Pt;
            double muon3Pions_Pion3_Pt_t3 = t3->muon3Pions_Pion3_Pt;
            double muon3Pions_Pion3_Eta_t3 = t3->muon3Pions_Pion3_Pt;
            
              if (muon3Pions_Muon_Pt_t3>muonPtCut && fabs(muon3Pions_Muon_Eta_t3)<muonPionEtaCut&& muon3Pions_Pion1_Pt_t3>pionPtCut && muon3Pions_Pion2_Pt_t3>pionPtCut && muon3Pions_Pion3_Pt_t3>pionPtCut &&  fabs(muon3Pions_Pion1_Eta_t3)<muonPionEtaCut &&  fabs(muon3Pions_Pion2_Eta_t3)<muonPionEtaCut &&  fabs(muon3Pions_Pion3_Eta_t3)<muonPionEtaCut){
                  hPt3->Fill(muon3Pions_Muon_Pt_t3);
            }
        } // end of the for loop on events
  //  }

    // Create a new canvas and set its properties
    auto c1 = new TCanvas("c1", "Muon3Pion Pt", 800, 600);
    setCanvasProperties(c1);
    
    // Divide the canvas into two parts with different sizes
    TPad *upperPad = new TPad("upperPad", "upperPad", 0.0, 0.33, 1.0, 1.0);
    upperPad->SetBottomMargin(0.0); // remove the bottom margin of the upper pad
    upperPad->Draw();

    TPad *lowerPad = new TPad("lowerPad", "lowerPad", 0.0, 0.0, 1.0, 0.32);
    lowerPad->SetTopMargin(0.0); // remove the top margin of the lower pad
    lowerPad->SetBottomMargin(0.4); // increase the bottom margin of the lower pad
    lowerPad->Draw();

    // Draw the histograms in the upper pad
    upperPad->cd();
    
   // hPt1->Rebin(5);
    
 /*
    hPt1 ->Scale(CROSSSECTION_A01);
    hPt2 ->Scale(CROSSSECTION_A0);
    hPt3 ->Scale(CROSSSECTION_A_01);
 */
  
    hPt1 ->Scale(1/hPt1->Integral());
    hPt2 ->Scale(1/hPt2->Integral());
    hPt3 ->Scale(1/hPt3->Integral());
    
    hPt1->Draw();
    hPt2->Draw("same");
    hPt3->Draw("same");

    
    hPt1->GetXaxis()->SetRangeUser(2, 8);


    // Divide the canvas into two pads: the upper pad for the histograms and the lower pad for the ratio plot


    TLegend *leg1 = new TLegend(0.3, 0.4, 0.9, 0.9);
    leg1->AddEntry("","P_{T #mu}>2.5,P_{T #pi}>pionPtCut,|#eta|<muonPionEtaCut ", "1");
    leg1->AddEntry(hPt1, Form("a_tau= 0.1 (Entries=%d, Mean=%.2f)", int(hPt1->GetEntries()), hPt1->GetMean()/*, h11->GetRMS()*/));
    leg1->AddEntry(hPt2, Form("a_tau= 0 (Entries=%d, Mean=%.2f)", int(hPt2->GetEntries()), hPt2->GetMean()/*, h21->GetRMS()*/));
    leg1->AddEntry(hPt3, Form("a_tau= -0.1 (Entries=%d, Mean=%.2f)", int(hPt3->GetEntries()), hPt3->GetMean()/*, h21->GetRMS()*/));
    
    
    leg1->Draw();
    
    // Create a new histogram for the ratios
    TH1F* hRatio1 = (TH1F*)hPt1->Clone("hRatio1");
    hRatio1->Divide(hPt2);
    hRatio1->SetLineColor(kRed);
    hRatio1->SetMarkerColor(kRed);

    TH1F* hRatio2 = (TH1F*)hPt3->Clone("hRatio2");
    hRatio2->Divide(hPt2);
    hRatio2->SetLineColor(kGreen);
    hRatio2->SetMarkerColor(kGreen);

    // Draw the ratio histograms on the lower pad
   // c1->cd(2);
   // hRatio1->Draw();
   // hRatio2->Draw("same");

    lowerPad->cd();
    hRatio1->Draw();
    hRatio2->Draw("same");

    //lowerPad->SetTickx();
    //lowerPad->SetTicky();
    //TGaxis::SetMaxDigits(3);
    hRatio1->GetXaxis()->SetTitleSize(0.15);
    hRatio1->GetXaxis()->SetLabelSize(0.12);
    hRatio1->GetXaxis()->SetNdivisions(12);
    hRatio1->GetYaxis()->SetNdivisions(8);
    hRatio1->GetYaxis()->SetTitleSize(0.06);
    hRatio1->GetYaxis()->SetTitle("Ratio to a_tau =0");
    
    // Set the y-axis range for the ratio plot
    hRatio1->GetYaxis()->SetRangeUser(0.5, 1.5);

    // Add a horizontal line at y=1 for reference
    auto line = new TLine(hRatio1->GetXaxis()->GetXmin(), 1.0, hRatio1->GetXaxis()->GetXmax(), 1.0);
    line->SetLineStyle(2);
    line->Draw();

    // Save the canvas as a PDF file
    c1->Print("Muon3PionPdf/Muon3Pion_MuonPt.pdf");

  cout << "\n";
}
