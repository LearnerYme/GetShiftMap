#include "ShiftFitMaker.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TF1.h"

void ShiftFitMaker::Init() {
    h1 = 0;
    gaus = new TF1("gaus", "gaus", -5, 5);
    gaus->SetParLimits(1, -2.5, 2.5);
}

void ShiftFitMaker::GetProjectionFromTH2(TH2F* h2, double p, int charge) {
    /*
        charge should be 1 for positive and -1 for negative
    */
    int bin = h2->GetYaxis()->FindBin(p*charge);
    h1 = (TH1F*)h2->ProjectionX("_px", bin, bin);
}

void ShiftFitMaker::GetProjectionFromTH3(TH3F* h3, double y, double pT, int charge) {
    /*
        charge should be 1 for positive and -1 for negative
    */
    int biny = h3->GetYaxis()->FindBin(y);
    int binz = h3->GetZaxis()->FindBin(pT*charge);
    h1 = (TH1F*)h3->ProjectionX("_px", biny, biny, binz, binz);
}

double ShiftFitMaker::GetShift() {
    if (h1->GetEntries() < 100) {
        return 0;
    } else {
        h1->Fit(gaus, "QN0", "", -3, 3);
        return gaus->GetParameter(1);
    }
}