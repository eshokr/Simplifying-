TH1F* createHistogram(const char* name, const char* title, int nbins, double xmin, double xmax,
                      Color_t lineColor = kBlack, Width_t lineWidth = 1,
                      const char* xTitle = "", const char* yTitle = "", Size_t xTitleSize = 0, Size_t yTitleSize = 0,
                      Size_t markerSize = 1.0, Color_t markerColor = kBlack, Color_t fillColor = 0, Style_t fillStyle = 0)
{
    TH1F* histogram = new TH1F(name, title, nbins, xmin, xmax);
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



// YOU CAN APPLY IT LIKE THIS
TH1F* h11= createHistogram("h11", "h11", 110, 0, 11, kBlue, 3, "XTITLE", "YTITLE", 0.05, 0.05);

