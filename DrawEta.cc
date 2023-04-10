#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"

void DrawEta() {
    // Open the root file and check if it is valid
    auto f1 = TFile::Open("outputsss.root");
    if (!f1 || f1->IsZombie()) {
        std::cerr << "Error: unable to open file 'outputsss.root'\n";
        return;
    }

    // Get the tree objects
    auto t1 = dynamic_cast<TTree*>(f1->Get("muon/MuonTree"));
    if (!t1) {
        std::cerr << "Error: unable to get TTree object from file\n";
        return;
    }

    // Create the histograms from the tree branches
    auto h1 = new TH1F("h1", "Muon Pt SoftMuon", 100, -5, 5);
    auto h2 = new TH1F("h2", "Muon Pt SoftStandAloneMuon", 100, -5, 5);
    auto h3 = new TH1F("h3", "Muon Pt SoftGlobalMuon", 100, -5, 5);
    t1->Draw("muonEtaSoftMuon>>h1");
    t1->Draw("muonEtaSoftStandAloneMuon>>h2");
    t1->Draw("muonEtaSoftGlobalMuon>>h3");

    // Create the canvas and set properties
    auto c1 = new TCanvas("c1", "Muon Pt", 800, 600);
    c1->SetGrid();
    c1->SetLogy();
    c1->SetLeftMargin(0.12);

    // Set line colors for the histograms
    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);
    h3->SetLineColor(kGreen);

    // Add histograms to the canvas and create a legend
    h1->Draw();
    h2->Draw("same");
    h3->Draw("same");
    auto leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    leg->AddEntry(h1, "SoftMuon", "l");
    leg->AddEntry(h2, "SoftStandAloneMuon", "l");
    leg->AddEntry(h3, "SoftGlobalMuon", "l");
    leg->Draw();

    // Save the canvas as a PDF file
    c1->Print("MuonPt.pdf");
}

