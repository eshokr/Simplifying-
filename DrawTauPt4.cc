#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"



void DrawTauPt4() {
    auto f1 = TFile::Open("tree_a_-01.root");
    auto f2 = TFile::Open("tree_a_-008.root");
    auto f3 = TFile::Open("tree_a_-004.root");
    auto f4 = TFile::Open("tree_a_004.root");
    auto f5 = TFile::Open("tree_a_008.root");
    auto f6 = TFile::Open("tree_a_01.root");
    if (!f1 || f1->IsZombie() || !f2 || f2->IsZombie() || !f3 || f3->IsZombie() || !f4 || f4->IsZombie() || !f5 || f5->IsZombie() || !f6 || f6->IsZombie()) {
        std::cerr << "Error: unable to open root file(s)\n";
        return;
    }

    // Get the tree objects
    auto t1 = dynamic_cast<TTree*>(f1->Get("informaiton"));
    auto t2 = dynamic_cast<TTree*>(f2->Get("informaiton"));
    auto t3 = dynamic_cast<TTree*>(f3->Get("informaiton"));
    auto t4 = dynamic_cast<TTree*>(f4->Get("informaiton"));
    auto t5 = dynamic_cast<TTree*>(f5->Get("informaiton"));
    auto t6 = dynamic_cast<TTree*>(f6->Get("informaiton"));
    if (!t1 || !t2 || !t3 || !t4 || !t5 || !t6) {
        std::cerr << "Error: unable to get TTree object from file(s)\n";
        return;
    }

    // Create the histograms from the tree branches
    auto h1 = new TH1F("h1", "Muon Pt SoftMuon", 60, 0, 30);
    auto h2 = new TH1F("h2", "Muon Pt SoftStandAloneMuon", 60, 0, 30);
    auto h3 = new TH1F("h3", "Muon Pt SoftGlobalMuon", 60, 0, 30);
    auto h4 = new TH1F("h4", "Muon Pt SoftMuon", 60, 0, 30);
    auto h5 = new TH1F("h5", "Muon Pt SoftStandAloneMuon", 60, 0, 30);
    auto h6 = new TH1F("h6", "Muon Pt SoftGlobalMuon", 60, 0, 30);
 

    t1->Draw("particle_pt_0>>h1");
    t1->Draw("particle_pt_1>>+h1");

    t2->Draw("particle_pt_1>>h2");
    t2->Draw("particle_pt_1>>+h2");

    t3->Draw("particle_pt_1>>h3");
    t3->Draw("particle_pt_1>>+h3");

    t4->Draw("particle_pt_1>>h4");
    t4->Draw("particle_pt_1>>+h4");

    t5->Draw("particle_pt_1>>h5");
    t5->Draw("particle_pt_1>>+h5");

    t6->Draw("particle_pt_1>>h6");
    t6->Draw("particle_pt_1>>+h6");


/*
    // Scale histograms by the respective factors
    h1->Scale(0.680211);
    h2->Scale(0.704972);
    h3->Scale(0.767259);
    h4->Scale(0.948142);
    h5->Scale(1.070202);
    h6->Scale(1.139995);
    
    
    h1->Scale(1/h1->Integral());
    h2->Scale(1/h2->Integral());
    h3->Scale(1/h3->Integral());
    h4->Scale(1/h4->Integral());
    h5->Scale(1/h5->Integral());
    h6->Scale(1/h6->Integral());
*/

// Create the canvas and set properties
    auto c1 = new TCanvas("c1", "Tau Pt", 800, 600);
    c1->SetGrid();
    c1->SetLogy();
    c1->SetLeftMargin(0.12);

    // Set line colors for the histograms
    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);
    h3->SetLineColor(kGreen);
    h4->SetLineColor(kBlack);
    h5->SetLineColor(kOrange +3);
    h6->SetLineColor(kBlue -6);
    // Add histograms to the canvas and create a legend

    h6->GetXaxis()->SetTitle("leading tau p_{T} GeV/c");
    h6->GetYaxis()->SetTitle("no of enentries/bin * cross section(mb)");

    h6->Draw();
    h5->Draw("same");
    h4->Draw("same");
    h3->Draw("same");
    h2->Draw("same");
    h1->Draw("same");
    
    
    auto leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    leg->AddEntry(h6, " 0.1", "l");
    leg->AddEntry(h5, " 0.08", "l");
    leg->AddEntry(h4, " 0.04", "l");
    leg->AddEntry(h2, "-0.04", "l");
    leg->AddEntry(h3, "-0.08", "l");
    leg->AddEntry(h1, "-0.1", "l");
   

    leg->Draw();

    // Save the canvas as a PDF file
    c1->Print("TauPt.pdf");
}
