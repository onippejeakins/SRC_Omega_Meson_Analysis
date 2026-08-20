#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ROOT/RDataFrame.hxx>
#include <TH2D.h>
#include <TH1.h>
#include <ROOT/RDF/HistoModels.hxx>

using namespace ROOT;
using namespace std;
using namespace ROOT::Detail::RDF;




void stan(string inputfilename, string treename, string outhistname){
	TChain chain(treename.c_str());
  chain.Add(inputfilename.c_str());

  RDataFrame rdf_raw(chain);

  cout << "Defining variables...\n";
	auto rdf_def = rdf_raw
	.Define("d_p4_kin", "TLorentzVector(0, 0, 0, 1.875613)")
	.Define("n_p4_kin", "-pip_p4_kin - pim_p4_kin - p_p4_kin - g1_p4_kin - g2_p4_kin + beam_p4_kin + d_p4_kin")
	.Define("n_mass", "n_p4_kin.M()")
	.Define("pi0_p4_kin", "g1_p4_kin + g2_p4_kin")
	.Define("pi0_mass", "pi0_p4_kin.M()")
	.Define("pi3_p4_kin", "pip_p4_kin +pim_p4_kin + pi0_p4_kin")
	.Define("pi3_mass", "pi3_p4_kin.M()")
	.Define("phi_omega", "pi3_p4_kin.Phi()*TMath::RadToDeg()");

	cout << "Defining Filters...\n";
	auto rdf_no_filter = rdf_def;

	int N_filters=1;

	ROOT::RDF::RNode rdfs [] = {rdf_no_filter };

	string labels[] = {"no cuts"};

	cout << "Creating histogram file...\n";
	TFile * histfile = new TFile (outhistname.c_str(),"RECREATE");
	histfile->cd();

	cout << "Constructing histograms...\n";
	vector <TH1D*> histslist;
	vector<ROOT::RDF::RResultPtr<TH1D>> hists;
  vector<ROOT::RDF::RResultPtr<TH2D>> hists2d;

	for (int i = 0; i < N_filters; i++) {
			auto rdf = rdfs[i];
    	string label = labels[i];
    	cout << label << "\n";

			auto h_miss_n = rdf.Histo1D({("miss_n_" + label).c_str(), ";n_p4_kin [GeV]", 100, 0, 3}, "n_mass", "accidweight");
			hists.push_back(h_miss_n); 
			auto h_pi3 = rdf.Histo1D({("pi3_" + label).c_str(), ";pi3 [GeV]", 300, 0, 4}, "pi3_mass", "accidweight");
			hists.push_back(h_pi3);
			auto h_pi0 = rdf.Histo1D({("pi0_" + label).c_str(), ";pi0 [GeV]", 100, 0, 0.5}, "pi0_mass", "accidweight");
			hists.push_back(h_pi0);
			auto h_phi = rdf.Histo1D({("phi_" + label).c_str(), ";phi [degrees]", 90, -180, 180}, "phi_omega", "accidweight");
			hists.push_back(h_phi);
}


cout << "Writing out histograms...\n";

  for (ROOT::RDF::RResultPtr<TH1D> hist : hists)
    {
			hist->Write();
    }
 /* for (ROOT::RDF::RResultPtr<TH2D> hist : hists2d)
    {
      hist->Write();
    }*/
histfile -> Close();

}





