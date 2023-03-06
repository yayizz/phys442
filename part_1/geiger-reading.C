{
	TCanvas *pCanvas1 = new TCanvas();
	pCanvas1->SetWindowSize(1400,900);
	pCanvas1->SetTitle("Canvas");

	TGraph *pGraph = new TGraph("./geiger-voltage.txt");
	pGraph->SetTitle("Geiger-Muller Voltage Measurements ; Supply Voltage (V) ; Count (per 100s)");
	pGraph->SetLineWidth(2);
	pGraph->Draw("AC*");


}