#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TH2.h"

using namespace std;

int main(int argc, char ** argv)
{
  if (argc != 4)
    {
      cerr << "Wrong number of arguments. Instead use\n"
	   << " /path/to/output name_of_th2 /path/to/input/file\n\n";
      return -1;
    }

  TFile *inf = new TFile(argv[3]);
  TH2D * h2 = (TH2D*)inf->Get(argv[2]);

  ofstream outf(argv[1]);

  for (int binx=0 ; binx <= h2->GetXaxis()->GetNbins() ; binx++)
    {
      for (int biny=0 ; biny <= h2->GetYaxis()->GetNbins() ; biny++)
	{
	  outf << h2->GetXaxis()->GetBinCenter(binx) << " "
	       << h2->GetYaxis()->GetBinCenter(biny) << " "
	       << h2->GetBinContent(binx,biny) << " " 
	       << h2->GetBinError(binx,biny) << "\n";
	}
      outf << "\n";
    }
    
  outf.close();
  return 0;
}
