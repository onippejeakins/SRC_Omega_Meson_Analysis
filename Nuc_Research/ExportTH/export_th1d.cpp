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
	   << " /path/to/output name_of_th1 /path/to/input/file\n\n";
      return -1;
    }

  TFile *inf=NULL;
  inf = new TFile(argv[3]);
  if ((!inf) || (inf->IsZombie()))
    {
      cerr << "Problem opening file " << argv[3] << "\n"
	   << "Aborting...\n\n";
      return -1;
    }
  
  TH1D * h1 = NULL;
  h1=(TH1D*)inf->Get(argv[2]);
  if (!h1)
    {
      cerr << "Problem accessing histogram " << argv[2] << "\n"
	   << "Aborting...\n\n";
      return -1;
    }
  
  ofstream outf(argv[1]);

  for (int binx=0 ; binx <= h1->GetXaxis()->GetNbins() ; binx++)
    {
      outf << h1->GetXaxis()->GetBinCenter(binx) << " "
	   << h1->GetBinContent(binx) << " " 
	   << h1->GetBinError(binx) << "\n";
    }
    
  outf.close();
  return 0;
}
