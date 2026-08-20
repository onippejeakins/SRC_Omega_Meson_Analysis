#include <iostream>
#include<list>
using namespace std;

std::list<int> numbers = {1, 1, 1, 1, 1, 2, 3, 4, 6};

double m1 = 0.6;
double m2 = 0.7;
double m3 = 0.9;
double m4 = 1.0;

double return_o_yield(TH1D* hist, double &yield_error);

double background(double *x, double *p){
double my_x = *x;
return p[0] + p[1] * my_x + p[2]* my_x * my_x + p[3] * my_x * my_x * my_x;


}

double t_bin_bounds[10]={0, 1, 2, 3, 4, 5, 7, 10, 14, 20};


int t_bin(double abs_t){
for( int i = 0; i < 8; i++){
	if(abs_t < t_bin_bounds[i+1])
		return i;

}
	return 8;
}



double sideband(double* x, double* p){
if(*x < m1)
	return 0;
if(*x > m4)
	return 0;
if(*x < m3 && *x > m2)
	return 0;

return background(x,p);
}

TF1 *sideband_fit = new TF1("sideband_fit", sideband, 0.6, 1, 4);
TF1 *background_model = new TF1("background model", background, 0.6, 1, 4);



void oliver(){
//open output of tiff, tree


TFile* in_file=new TFile("run_configs/output/output_45135_perp.root");
TFile* out_file = new TFile("oliver_out.root", "RECREATE");



// set up tree and branch addresses


TTree* T = (TTree*) in_file -> Get ("T");
double accidweight;
TLorentzVector *beam_p4_kin=NULL, *pim_p4_kin=NULL, *pip_p4_kin=NULL, *p_p4_kin=NULL, *pi0_p4_kin=NULL;

T -> SetBranchAddress("accidweight", &accidweight);
T -> SetBranchAddress("beam_p4_kin", &beam_p4_kin);
T -> SetBranchAddress("pim_p4_kin", &pim_p4_kin);
T -> SetBranchAddress("pip_p4_kin", &pip_p4_kin);
T -> SetBranchAddress("pi0_p4_kin", &pi0_p4_kin);
T -> SetBranchAddress("p_p4_kin", &p_p4_kin);


// setting up fitting function

TF1 *sideband_fit = new TF1("sideband_fit", sideband, 0.6, 1, 4);


//initialize hists, will need more info from tiff

TH1D* h1_e_beam = new TH1D("e_beam", "events that have passed tiff; beam energy [GeV]; Counts", 50, 8.1, 8.6);
TH2D* h2_phi_pi3_mass = new TH2D("phi_pi3_mass", " ; pi3 mass [GeV]; phi [degrees]", 150, 0, 1.5, 36, -180, 180);
TH2D* h2_abs_t_pi3_mass = new TH2D("t_pi3_mass", " ; pi3 mass [GeV]; -t [GeV^2]", 100, 0, 1.5, 20, 0, 20);
TH2D* h2_phi_pi3_mass_t[9];


for(int i =0; i<9; i++){
	char temp[100];
	snprintf(temp, 100, "phi_pi3_mass_t%d", i);
	h2_phi_pi3_mass_t[i] = new TH2D(temp, " ; pi3 mass [GeV]; phi [degrees]", 150, 0, 1.5, 36, -180, 180);


}


//loop over events in tree

for(int event = 0; event < T->GetEntries(); event++){
	T -> GetEvent(event);
	if(beam_p4_kin->E() > 8.1 && beam_p4_kin->E() < 8.6){
		TLorentzVector pi3_p4_kin = *pi0_p4_kin + *pip_p4_kin + *pim_p4_kin;
		double abs_t = -(*beam_p4_kin - pi3_p4_kin).M2();
		double phi_rad = pi3_p4_kin.Phi();





// fill, cuts



		h1_e_beam -> Fill(beam_p4_kin->E(), accidweight);
		h2_phi_pi3_mass -> Fill(pi3_p4_kin.M(), phi_rad*TMath::RadToDeg(), accidweight);
		h2_abs_t_pi3_mass -> Fill(pi3_p4_kin.M(), abs_t, accidweight);
		h2_phi_pi3_mass_t[t_bin(abs_t)] -> Fill(pi3_p4_kin.M(), phi_rad*TMath::RadToDeg(), accidweight);


}

}

ofstream output_txt("yields.txt");

for(int i = 0; i < 12; i++){
	char temp[100];
	snprintf(temp,sizeof(temp), "proj_x_%d", i);
	TH1D* proj_x = h2_phi_pi3_mass -> ProjectionX(temp, i*3, i*3+3);
	double yield_error;
	double omega_yield = return_o_yield(proj_x, yield_error);
	proj_x -> Write();
	output_txt << "omega yield for " << i*3+2 << " :" << omega_yield << " +/- " << yield_error  << "\n";
}

output_txt << "\n \n \n";



for(int i =0; i<9; i++){
	output_txt << t_bin_bounds[i] << " < |t| < " <<  t_bin_bounds[i+1] << "\n";
  h2_phi_pi3_mass_t[i]->Write();
	for(int j=0; j<12; j++){
		char temp[100];
		snprintf(temp, 100, "proj_x_%d_%d", i,j);
		TH1D* proj_x = h2_phi_pi3_mass_t[i] -> ProjectionX(temp, j*3+1, j*3+3);
		double yield_error;
		double omega_yield = return_o_yield(proj_x, yield_error);
		proj_x -> Write();
		output_txt << "omega yield for " << j*3+2 << " :" << omega_yield << " +/- " << yield_error  << "\n";




}

output_txt << "\n \n \n";

}


TH1D* proj_x_t_1 = h2_abs_t_pi3_mass -> ProjectionX("proj_x_t_1", 1, 1);
TH1D* proj_x_t_2 = h2_abs_t_pi3_mass -> ProjectionX("proj_x_t_2", 2, 2);
TH1D* proj_x_t_3 = h2_abs_t_pi3_mass -> ProjectionX("proj_x_t_3", 3, 3);
TH1D* proj_x_t_4 = h2_abs_t_pi3_mass -> ProjectionX("proj_x_t_4", 4, 4);
TH1D* proj_x_t_5 = h2_abs_t_pi3_mass -> ProjectionX("proj_x_t_5", 5, 5);
TH1D* proj_x_t_6 = h2_abs_t_pi3_mass -> ProjectionX("proj_x_t_6", 6, 7);
TH1D* proj_x_t_7 = h2_abs_t_pi3_mass -> ProjectionX("proj_x_t_7", 8, 10);
TH1D* proj_x_t_8 = h2_abs_t_pi3_mass -> ProjectionX("proj_x_t_8", 11, 14);
TH1D* proj_x_t_9 = h2_abs_t_pi3_mass -> ProjectionX("proj_x_t_9", 15, 20);


TH1D* projs[9] = {proj_x_t_1,proj_x_t_2, proj_x_t_3, proj_x_t_4, proj_x_t_5, proj_x_t_6, proj_x_t_7, proj_x_t_8, proj_x_t_9};

ofstream output_text ("omega_yield_t.txt");


for(int i = 0 ; i< 9; i++){
	double yield_error;
	double yield = return_o_yield(projs[i], yield_error);
	output_text << i << " " << yield << " " << yield_error << "\n";
	projs[i] -> Write();
}

output_text.close();



in_file -> Close();
output_txt.close();
out_file -> cd();


h1_e_beam -> Write();
h2_phi_pi3_mass -> Write();
h2_abs_t_pi3_mass -> Write();
out_file -> Close();

//extract 1d hist from 2d



}




double return_o_yield(TH1D* hist, double &yield_error){

hist -> Fit("sideband_fit");
double hist_int = hist -> IntegralAndError(hist->FindBin(m2), hist->FindBin(m3), yield_error);


background_model -> SetParameters(sideband_fit->GetParameters());

double bck_int = background_model -> Integral(m2,m3)/hist->GetBinWidth(1);
return hist_int-bck_int;


}



