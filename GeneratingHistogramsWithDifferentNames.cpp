
{
 // Written by Eslam Shokr
 // 24/11/2022
 
 // this code is written to generate histogram with variable name!!
 
 TF1 *f1 = new TF1("f1","abs(sin(x)/x)*sqrt(x)",0,20);
TH1F *myhist[4];

 const char* histname[4]  = { "histo_1", "histo_2", "histo_3", "histo_4" };
 
 for (int i = 0; i < 4; i++)
 std::cout << histname[i] << "\n";

int nbins=20,nfiles=5;
float xmin=0,xmax=20;
for (int i=0;i<4;i++) {
//sprintf(histname,"histo%d",i);
 myhist[i] = new TH1F(histname[i],"",nbins, xmin, xmax);
 
 for (int j=0;j<40;j++) {
  double r = f1->GetRandom(); 
   myhist[i]->Fill(r);
 }   
}

myhist[3] ->Draw("SAME");
  myhist[2] ->Draw("SAME");
  myhist[1] ->Draw("SAME");
}
