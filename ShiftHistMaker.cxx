#include "ShiftFitMaker.h"
#include "ShiftHistMaker.h"

#include "TH1F.h"
#include "TH2F.h"

void ShiftHistMaker::Init(const char* name1, const char* title1, int nBin1d, double x11d, double x21d, const char* name2, const char* title2, int nBinX2d, double x12d, double x22d, int nBinY2d, double y12d, double y22d) {
    h1 = new TH1F(name1, title1, nBin1d, x11d, x21d);
    h2 = new TH2F(name2, title2, nBinX2d, x12d, x22d, nBinY2d, y12d, y22d);

    sfm = new ShiftFitMaker();
    sfm->Init();

    charge = 1;
}

void ShiftHistMaker::SetCharge(int q) {
    charge = q;
}

void ShiftHistMaker::Calc1DHist(TH2F* h2) {
    int nBinsX = h1->GetNbinsX(); 
    double p;
    for (int i=1; i<nBinsX+1; i++) {
        p = h1->GetXaxis()->GetBinCenter(i);
        sfm->GetProjectionFromTH2(h2, p, charge);
        h1->SetBinContent(i, sfm->GetShift());
    }
}

void ShiftHistMaker::Calc2DHist(TH3F* h3) {
    int nBinsX = h2->GetNbinsX();
    int nBinsY = h2->GetNbinsY();
    double y, pT;
    for (int i=1; i<nBinsX+1; i++) {
        y = h2->GetXaxis()->GetBinCenter(i);
        for (int j=1; j<nBinsY+1; j++) {
            pT = h2->GetYaxis()->GetBinCenter(j);
            sfm->GetProjectionFromTH3(h3, y, pT, charge);
            h2->SetBinContent(i, j, sfm->GetShift());
        }
    }
}

TH1F* ShiftHistMaker::Get1DHist() {
    return h1;
}

TH2F* ShiftHistMaker::Get2DHist() {
    return h2;
}
