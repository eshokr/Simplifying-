# this code to draw a histogram with variable bin width, it is helpful if you have low stats at the tail of the histogram.
# Eslam Shokr
# 11-5-2023

import ROOT

NOOFBINS = 4
edges = array.array('d', [0.0, 0.2, 0.3, 0.6,  1.0])

# Create the histogram
hist = ROOT.TH1D(
    "h1",
    "Hist with variable bin width",
    NOOFBINS,
    edges
)

for i in range (2, 8):
    hist.Fill(i/10)


# Customize the histogram
hist.SetLineColor(ROOT.kRed)
hist.GetXaxis().SetTitle("X")
hist.GetYaxis().SetTitle("Y")

# Create a canvas and draw the histogram
canvas = ROOT.TCanvas("canvas", "Histogram")
hist.Draw()
canvas.Draw()

# If you are using a script, you can save the histogram to a file
canvas.SaveAs("histogram.png")
