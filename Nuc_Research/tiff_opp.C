double counter(TH1D* mass_spectrum);
double counter_fit(TH1D* mass_spectrum, TF1* sb, TF1* bg);
double side_band(double* x, double* p);
double background(double* x, double* p);
//TLorentzVector N = (0,0,0,0.938);
double mN = 0.938;

void tiff(string inputfilename,string outputfilename){
TFile* inputfile = new TFile(inputfilename.c_str());
string inputtreename("gd_pi0pippimprotmissn__B4_F4_T1_S4");
TTree* inputtree = 0; 
inputtree = (TTree*) inputfile -> Get(inputtreename.c_str());

if(!inputfile){
	cout << "i could not find inputfile \n"
	<< "i was looking for file " << inputfilename << "\n";
	return;
}

if(!inputtree){
	cout << "could not find inputtree \n"
	<< "i was looking for file " << inputtreename << "\n";
	return;
}

cout << "saved inputtree to " << inputtree << "\n";



//setting up branches of inputtree


TLorentzVector *pip_p4_kin=NULL, *pim_p4_kin=NULL, *p_p4_kin=NULL, *g1_p4_kin=NULL, *g2_p4_kin=NULL, *beam_p4_kin=NULL;
double accidweight;
inputtree -> SetBranchAddress("pip_p4_kin", &pip_p4_kin);
inputtree -> SetBranchAddress("pim_p4_kin", &pim_p4_kin);
inputtree -> SetBranchAddress("p_p4_kin", &p_p4_kin);
inputtree -> SetBranchAddress("g1_p4_kin", &g1_p4_kin);
inputtree -> SetBranchAddress("g2_p4_kin", &g2_p4_kin);
inputtree -> SetBranchAddress("beam_p4_kin", &beam_p4_kin);
inputtree -> SetBranchAddress("accidweight", &accidweight);

//tf
TF1* my_side_band = new TF1("my_side_band", side_band, 0.5, 1.1, 4);
TF1* my_background = new TF1("my_background", background, 0.5, 1.1, 4);

//loop over all events
cout << "Creating histogram file...\n";
	TFile * histfile = new TFile(outputfilename.c_str(),"RECREATE");
	histfile->cd();
TTree* outputtree = new TTree("T", "output");
outputtree -> Branch("accidweight", &accidweight, "accidweight/D");
outputtree -> Branch("beam_p4_kin", &beam_p4_kin);

vector<TH1D*> h1_list;
vector<TH2D*> h2_list;

TH1D* hist = new TH1D("hist", "test histogram", 100, 0, 10);
h1_list.push_back(hist);

TH1D* h_pi3_mass = new TH1D("pi3_mass", "all events; pi3_mass[GeV]; counts", 100, 0, 4);
h1_list.push_back(h_pi3_mass);

TH2D* h2_t_pi3_mass = new TH2D("t_pi3_mass", "all events; pi3_mass[GeV]; -t[GeV^2]; counts", 100, 0, 4, 100, 0, 20);
h2_list.push_back(h2_t_pi3_mass);

TH2D* h2_t_pi3_mass_o_enhanced = new TH2D("t_pi3_mass_omega_enhanced", "omega enhanced; pi3_mass [GeV]; -t[GeV^2]; counts", 100, 0.5, 1.0, 100, 0, 20);
h2_list.push_back(h2_t_pi3_mass_o_enhanced);

TH1D* h_pi3_mass_o_enhanced = new TH1D("pi3_mass_omega_enhanced", "omega enhanced; pi3_mass [GeV]; counts", 100, 0.5, 1);
h1_list.push_back(h_pi3_mass_o_enhanced);

TH1D* h_pi3_mass_e_enhanced = new TH1D("pi3_mass_eta_enhanced", "eta enhanced; pi3_mass [GeV]; counts", 100, 0.4, 0.7);
h1_list.push_back(h_pi3_mass_e_enhanced);

TH1D* h_phi_mmom_o_enhanced = new TH1D("phi_missing_momentum_omega_enhanced", ";phi of missing momentum; counts", 40, -180, 180);
h1_list.push_back(h_phi_mmom_o_enhanced);

TH2D* h2_t_pi3_mass_e_enhanced = new TH2D("t_pi3_mass_eta_enhanced", "eta enhanced; pi3_mass [GeV]; -t [GeV^2]; counts", 100, 0.5, 1.0, 100, 0, 20);
h2_list.push_back(h2_t_pi3_mass_e_enhanced);

TH1D* h_mmom = new TH1D("missing momentum", ";Missing Momentum [GeV]; counts", 100, -2, 2);
h1_list.push_back(h_mmom);

TH1D* h_angle_mmom = new TH1D("angle_missing_momentum", ";angle of missing momentum; counts", 100, 0, 180);
h1_list.push_back(h_angle_mmom);

TH1D* h_mmom_o_enhanced = new TH1D("missing_momentum_omega_enhanced", ";Missing Momentum [GeV]; counts", 100, -2, 2);
h1_list.push_back(h_mmom_o_enhanced);

TH1D* h_angle_mmom_o_enhanced = new TH1D("angle_missing_momentum_omega_enhanced", ";angle of missing momentum; counts", 100, 0, 180);
h1_list.push_back(h_angle_mmom_o_enhanced);

TH1D* h_mmom_e_enhanced = new TH1D("missing_momentum_eta_enhanced", ";missing momentum; counts", 100, -2, 2);
h1_list.push_back(h_mmom_e_enhanced);

TH1D* h_angle_mmom_e_enhanced = new TH1D("angle_missing_momentum_eta_enhanced", ";angle of missing momentum; counts", 100, 0, 180);
h1_list.push_back(h_angle_mmom_e_enhanced);

TH1D* h_beam_energy = new TH1D("beam_energy", "beam energy [GeV]; counts", 100, 0, 10);
h1_list.push_back(h_beam_energy);

TH1D* h_beam_peak = new TH1D("beam peak", "beam energy, counts", 100, 0, 10);
h1_list.push_back(h_beam_peak);

TH1D* h_phi_beam_peak = new TH1D("phi_missing_momentum_peak", ";angle of phi; counts", 50, -180, 180);
h1_list.push_back(h_phi_beam_peak);

TH1D* h_phi_src_mmom_o_enhanced = new TH1D("phi_missing_momentum_src_omega_enhanced", ";phi of src missing momentum; counts", 40, -180, 180);
h1_list.push_back(h_phi_src_mmom_o_enhanced);

TH1D* h_phi_nonsrc_mmom_o_enhanced = new TH1D("phi_missing_momentum_nonsrc_omega_enhanced", ";phi of src missing momentum; counts", 40, -180, 180);
h1_list.push_back(h_phi_nonsrc_mmom_o_enhanced);

TH1D* h_theta_mmom_beampeak_o_enhanced = new TH1D("theta_missing_momentum_omega_enhanced", ";angle of missing momentum; counts", 100, 0, 180);
h1_list.push_back(h_theta_mmom_beampeak_o_enhanced);

TH1D* h_phi_src_o_enhanced = new TH1D("phi_src_omega_enhanced", ";phi of src missing momentum; counts", 12, -180, 180);
h1_list.push_back(h_phi_src_o_enhanced);

TH1D* h_phi_nonsrc_o_enhanced = new TH1D("phi_nonsrc_omega_enhanced", ";phi of src missing momentum; counts", 12, -180, 180);
h1_list.push_back(h_phi_nonsrc_o_enhanced);



for (int i=0 ; i<h1_list.size() ; i++)
{
	h1_list[i]->Sumw2();
}

for (int i=0 ; i<h2_list.size() ; i++)
{
	h2_list[i]->Sumw2();
}


const int n_events = inputtree -> GetEntries();
cout << "beginning loop over " << n_events << "\n";
for(int event=0; event < n_events; event++){
	inputtree -> GetEvent(event);
	TLorentzVector pi3_p4_kin = *pip_p4_kin + *pim_p4_kin + *g1_p4_kin + *g2_p4_kin;

	double abs_t = -(*beam_p4_kin - pi3_p4_kin).M2();

	TLorentzVector X_p4_kin = -((pi3_p4_kin + *p_p4_kin) - (*beam_p4_kin + TLorentzVector(0,0,0,1.876)));
	//double X_p3_kin = X_p4_kin.P();
	double X_theta_kin = X_p4_kin.Theta() * 180/M_PI;	

	//if(event%10000==0){
		//cout << "working on event " << event << "\n";
	//}
	//cout << pip_p4_kin -> E() << "\n";
	//cout << &pip_p4_kin << " " << pip_p4_kin << "\n";
	//cout << accidweight << "\n";

	hist->Fill(pip_p4_kin->E(), accidweight);
	h_beam_energy->Fill(beam_p4_kin->E(), accidweight);
	if(beam_p4_kin->E() > 8.1 && beam_p4_kin->E() < 8.6){
		h_beam_peak->Fill(beam_p4_kin->E());
		h_phi_beam_peak->Fill(pi3_p4_kin.Phi()*180/M_PI, accidweight);
	}


	h_pi3_mass -> Fill(pi3_p4_kin.M(), accidweight);
	h2_t_pi3_mass -> Fill(pi3_p4_kin.M(), abs_t, accidweight);
	if(pi3_p4_kin.M() < 0.83 && pi3_p4_kin.M() > 0.75){
		double pi3_mass_omega_enhanced = pi3_p4_kin.M();
		h2_t_pi3_mass_o_enhanced -> Fill(pi3_mass_omega_enhanced, abs_t, accidweight);
		h_pi3_mass_o_enhanced -> Fill(pi3_mass_omega_enhanced, accidweight);
		TLorentzVector X_p4_kin_o_enhanced = -((pi3_p4_kin + *p_p4_kin) - (*beam_p4_kin + TLorentzVector(0,0,0,1.876)));
		double X_theta_kin_o_enhanced = X_p4_kin_o_enhanced.Theta() * 180/M_PI;
			if(beam_p4_kin->E() > 8.1 && beam_p4_kin->E() < 8.6){
				double X_phi_kin_o_enhanced = X_p4_kin_o_enhanced.Phi() * 180/M_PI;
				double X_theta_kin_o_enhanced = X_p4_kin_o_enhanced.Theta() * 180/M_PI;
				h_theta_mmom_beampeak_o_enhanced -> Fill(X_theta_kin_o_enhanced, accidweight);
				h_phi_mmom_o_enhanced->Fill(X_p4_kin.Phi()*180/M_PI, accidweight);
			}
		if (X_p4_kin_o_enhanced.P() > .35 && beam_p4_kin->E() > 8.1 && beam_p4_kin->E() < 8.6){
			double X_phi_kin_src_o_enhanced = X_p4_kin_o_enhanced.Phi()* 180/M_PI;
			h_phi_src_mmom_o_enhanced->Fill(X_phi_kin_src_o_enhanced, accidweight);
			h_phi_src_o_enhanced->Fill((pi3_p4_kin.Phi()* 180/M_PI), accidweight);
		}
		if (X_p4_kin_o_enhanced.P() < .25 && beam_p4_kin->E() > 8.1 && beam_p4_kin->E() < 8.6){
			double X_phi_kin_nonsrc_o_enhanced = X_p4_kin_o_enhanced.Phi()* 180/M_PI;
			h_phi_nonsrc_mmom_o_enhanced->Fill(X_phi_kin_nonsrc_o_enhanced, accidweight);
			h_phi_nonsrc_o_enhanced->Fill((pi3_p4_kin.Phi()* 180/M_PI), accidweight);
		}


		h_angle_mmom_o_enhanced -> Fill(X_theta_kin_o_enhanced, accidweight);
		h_mmom_o_enhanced -> Fill(X_p4_kin_o_enhanced.P(), accidweight);
	}
	if(pi3_p4_kin.M() < 0.57 && pi3_p4_kin.M() > 0.53){
		double pi3_mass_eta_enhanced = pi3_p4_kin.M();
		h2_t_pi3_mass_e_enhanced -> Fill(pi3_mass_eta_enhanced, abs_t, accidweight);
		h_pi3_mass_e_enhanced -> Fill(pi3_mass_eta_enhanced, accidweight);
		TLorentzVector X_p4_kin_e_enhanced = -((pi3_p4_kin + *p_p4_kin) - (*beam_p4_kin + TLorentzVector(0,0,0,1.876)));
		double X_theta_kin_e_enhanced = X_p4_kin_e_enhanced.Theta() * 180/M_PI;
		h_angle_mmom_e_enhanced -> Fill(X_theta_kin_e_enhanced, accidweight);
		h_mmom_e_enhanced -> Fill(X_p4_kin_e_enhanced.P(), accidweight);
	}
//if(*beam_p4_kin.E()

	//h2_beam_pi3_mass->Fill(pi3_p4_kin.M(), beam_p4_kin.M(), accidweight);
	h_mmom -> Fill(X_p4_kin.P(), accidweight);
	h_angle_mmom -> Fill(X_theta_kin, accidweight);


outputtree -> Fill();

}
	
TH1D* h1_pi_mass = (TH1D*) h2_t_pi3_mass_o_enhanced -> ProjectionX("1d_pi_mass", 1, 10);

for (int i=0 ; i<h1_list.size() ; i++)
{
	h1_list[i]->Write();
}

for (int i=0 ; i<h2_list.size() ; i++)
{
	h2_list[i]->Write();
}



//double yield = counter_fit(h1_pi_mass, my_side_band, my_background);


//making histograms (or at least attempting to)
histfile-> cd();
//hist->Write();
//h2_t_pi3_mass->Write();
//h2_t_pi3_mass_o_enhanced->Write();
//h2_t_pi3_mass_e_enhanced->Write();
//h_pi3_mass->Write();
//h_pi3_mass_o_enhanced->Write();
//h_pi3_mass_e_enhanced->Write();
//h2_beam_pi3_mass->Write();
//h_mmom -> Write();
//h_angle_mmom -> Write();
//h_mmom_o_enhanced -> Write();
//h_phi_mmom_o_enhanced -> Write();
//h_angle_mmom_o_enhanced -> Write();
//h_mmom_e_enhanced->Write();
//h_angle_mmom_e_enhanced->Write();
//h_beam_energy -> Write();
//h_beam_peak -> Write();
//h_phi_beam_peak->Write();

outputtree -> Write();

cout << "drew a histogram \n";



}


double counter(TH1D* mass_spectrum){
int leftbin = mass_spectrum->FindBin(0.65);
int rightbin = mass_spectrum->FindBin(0.9);
double integral = mass_spectrum->Integral(leftbin, rightbin);
double trap_area = 0.5*(mass_spectrum->GetBinContent(leftbin) + mass_spectrum->GetBinContent(rightbin))*(rightbin-leftbin+1);
cout << integral-trap_area;
return integral-trap_area;


}

double side_band(double* x, double* p){
if(*x < 0.5)
	return 0;
if(*x > 1.1)
	return 0;
if((*x > 0.65)&&(*x < 0.95))
	return 0;
return background(x, p);
}


double background(double* x, double* p){


return p[0]+p[1]*x[0]+p[2]*x[0]*x[0]+p[3]*x[0]*x[0]*x[0];


}


double counter_fit(TH1D* mass_spectrum, TF1* sb, TF1* bg){
mass_spectrum->Fit(sb, "", "",  0.5, 1.1);
bg->SetParameters(sb->GetParameters());
int leftbin = mass_spectrum->FindBin(0.65);
int rightbin = mass_spectrum->FindBin(0.9);
double integral = mass_spectrum->Integral(leftbin, rightbin);
cout << "signal+background = " << integral << "\n";
double yield = integral - bg->Integral(0.65, 0.9) / mass_spectrum->GetBinWidth(leftbin);
cout << "we estimate the signal only to be " << yield << "\n";
return yield;

}

