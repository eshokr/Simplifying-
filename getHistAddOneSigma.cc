#include <iostream>
#include <TFile.h>
#include <TH1.h>


void GenerateSigmaHistograms(const char* originalHistName, const char* outputRootFile) {
    // Open the input file
    TFile* inputFile = new TFile("rootFileName.root", "READ");

    // Get the directory from the input file
    TDirectory* dir = inputFile->GetDirectory("3prong");

    // Get the original histogram from the directory
    TH1F* originalHist = (TH1F*)dir->Get(originalHistName);

    // Create histograms for one sigma up and one sigma down
    TString twoSigmaUpHistName = TString(originalHistName) + "_twoSigmaUp";
    TString oneSigmaUpHistName = TString(originalHistName) + "_oneSigmaUp";
    TString oneSigmaDownHistName = TString(originalHistName) + "_oneSigmaDown";

    TH1F* twoSigmaUpHist = new TH1F(twoSigmaUpHistName, "Original +2 Sigma", originalHist->GetNbinsX(), originalHist->GetXaxis()->GetXmin(), originalHist->GetXaxis()->GetXmax());
    
    TH1F* oneSigmaUpHist = new TH1F(oneSigmaUpHistName, "Original +1 Sigma", originalHist->GetNbinsX(), originalHist->GetXaxis()->GetXmin(), originalHist->GetXaxis()->GetXmax());
    TH1F* oneSigmaDownHist = new TH1F(oneSigmaDownHistName, "Original -1 Sigma", originalHist->GetNbinsX(), originalHist->GetXaxis()->GetXmin(), originalHist->GetXaxis()->GetXmax());

    // Loop over each bin and calculate one sigma up and one sigma down values
    for (int bin = 1; bin <= originalHist->GetNbinsX(); ++bin) {
        double content = originalHist->GetBinContent(bin);
        double error = originalHist->GetBinError(bin);

        double contentTwoSigmaUp = content + 2*error;
        double contentOneSigmaUp = content + error;
        double contentOneSigmaDown = content - error;

        twoSigmaUpHist->SetBinContent(bin, contentTwoSigmaUp);
        twoSigmaUpHist->SetBinError(bin, error);

        oneSigmaUpHist->SetBinContent(bin, contentOneSigmaUp);
        oneSigmaUpHist->SetBinError(bin, error);

        oneSigmaDownHist->SetBinContent(bin, contentOneSigmaDown);
        oneSigmaDownHist->SetBinError(bin, error);

    }

// Save the histograms to the output root file
// TFile* outputFile = new TFile(outputRootFile, "RECREATE");
//  TDirectory* outputDir = outputFile ->mkdir("3prong");
//  TDirectory* outputDir = outputFile->GetDirectory("3prong");

    // Save the histograms to the output root file
    TFile* outputFile = nullptr;
    TDirectory* outputDir = nullptr;

    if (outputRootFile) {
        outputFile = new TFile(outputRootFile, "UPDATE");
    } else {
        outputFile = new TFile(outputRootFile, "CREATE");
    }

    if (outputFile && !outputFile->IsZombie()) {
        outputDir = outputFile->GetDirectory("3prong");
        if (!outputDir)
            outputDir = outputFile->mkdir("3prong");
    } else {
        cout << "Failed to open the output file: " << outputRootFile << endl;
        return;
    }
    
    
    outputDir->cd();
    
    twoSigmaUpHist->Write();
    oneSigmaUpHist->Write();
    oneSigmaDownHist->Write();
    outputFile->Close();

}




void getHistAddOneSigma() {
  const char* outputRootFile = "output1.root";
  const char* originalHistName = "MC-signal";
  GenerateSigmaHistograms(inputRootFile, originalHistName, outputRootFile);
  
  
}
