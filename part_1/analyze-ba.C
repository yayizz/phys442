void analyze_ba(void){

	//Cs-137

	TCanvas *pCanvas = new TCanvas();
	pCanvas->SetWindowSize(1400,900);
	pCanvas->SetTitle("Ba-133 measurements");
	TGraph *pGraph = new TGraph("./data/ba-133.txt");
	pGraph->SetTitle("Ba-133 measurements");
	//pGraph->Draw("A*");
	gStyle->SetOptFit(111);
	//histogram declerations
	TH1D *pH_one_sec = new TH1D("histo_one","Ba133 1s measurement ; Number of count ; Frequency",9,0,9);
	
	TH1D *pH_ten_sec = new TH1D("histo_ten","Ba133 10s measurement ; Number of count ; Frequency",10,5,40);
	


	//fit function declerations and initializations

	

	//gaus1s
	
	/* 
	*/
	TF1 *pGaus_1s = new TF1("gaus_1s","[0]*TMath::Gaus(x,[1],[2])",0,10);
	pGaus_1s->SetParameters(29,4,1);
	pGaus_1s->SetLineColor(kGreen);
	pGaus_1s->SetLineWidth(3);
	pGaus_1s->SetParNames("amplitude","mean","std");

	//pois1s

/*
*/
	TF1 *pPoisson_1s = new TF1("poisson_1s","[0]*TMath::Poisson(x,[1])",1,8);
	pPoisson_1s->SetParameters(100,4);
	pPoisson_1s->SetLineColor(kBlue);
	pPoisson_1s->SetLineWidth(5);
	pPoisson_1s->SetParNames("amplitude","mean");

	//gaus10s

/*
*/
	TF1 *pGaus_10s = new TF1("gaus_10s","[0]*TMath::Gaus(x,[1],[2])",8,37);
	pGaus_10s->SetParameters(25,21,5);
	pGaus_10s->SetLineColor(kGreen);
	pGaus_10s->SetLineWidth(3);
	pGaus_10s->SetParNames("amplitude","mean","std");
	
	
	//pois10s

	TF1 *pPoisson_10s = new TF1("poisson_10s","[0]*TMath::Poisson(x,[1])",8,38);
	pPoisson_10s->SetParameters(10,20,5);
	pPoisson_10s->SetLineColor(kBlue);
	pPoisson_10s->SetLineWidth(5);
	pPoisson_10s->SetParNames("amplitude","mean");
/*
*/
	
	//declerations
	
	TF1 *pGaus_fit_1s,*pGaus_fit_10s,*pPoisson_fit_1s,*pPoisson_fit_10s;
	Double_t x,y;

	for(int i = 0; i< 100;i++)
	{
		x = pGraph->GetPointX(i);
		y = pGraph->GetPointY(i);

		pH_one_sec->Fill(x);
		pH_ten_sec->Fill(y);
	}
	pH_one_sec->GetXaxis()->SetTitle("Number of count");
	pH_one_sec->GetYaxis()->SetTitle("Frequency");
	
	pH_ten_sec->GetXaxis()->SetTitle("Number of count");
	pH_ten_sec->GetYaxis()->SetTitle("Frequency");
	

	pH_one_sec->Draw();
	pH_ten_sec->Draw();

	cout << "mean of measurements with one sec period: " << pH_one_sec->GetMean() << endl;
	cout << "std of measurements with one sec period: " << pH_one_sec->GetRMS() << endl;
	cout << "mean of measurements with ten sec period: " << pH_ten_sec->GetMean() << endl;
	cout << "std of measurements with ten sec period: " << pH_ten_sec->GetRMS() << endl;

	/*
	*/
	cout << "fitting gaussian to measurements with one sec period" << endl;
	pH_one_sec->Fit(pGaus_1s,"LR");
	pGaus_fit_1s = pH_one_sec->GetFunction("gaus_1s");
	
	cout << "fitting poisson to measurements with one sec period" << endl;
	pH_one_sec->Fit(pPoisson_1s,"+LR");
	pPoisson_fit_1s = pH_one_sec->GetFunction("poisson_1s");
	

	/*	
	*/
	cout << "fitting gaussian to measurements with ten sec period" << endl;
	pH_ten_sec->Fit(pGaus_10s,"LR");
	pGaus_fit_10s = pH_ten_sec->GetFunction("gaus_10s");

	cout << "fitting poisson to measurements with ten sec period" << endl;
	pH_ten_sec->Fit("poisson_10s","+LR");
	pPoisson_fit_10s = pH_ten_sec->GetFunction("poisson_10s");

	cout << "1s gaus fit chi2/ndf: "<< pGaus_fit_1s->GetChisquare()/pGaus_fit_1s->GetNDF() << endl;
	cout << "1s poisson fit chi2/ndf: "<< pPoisson_fit_1s->GetChisquare()/pPoisson_fit_1s->GetNDF() << endl;
	cout << "10s gaus fit chi2/ndf: " << pGaus_fit_10s->GetChisquare()/pGaus_fit_10s->GetNDF() << endl;
	cout << "10s poissons fit chi2/ndf: " << pPoisson_fit_10s->GetChisquare()/pPoisson_fit_10s->GetNDF() << endl;	
	

	/*
	*/

}
