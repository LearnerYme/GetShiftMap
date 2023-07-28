#include "ShiftFitMaker.h"
#include "ShiftHistMaker.h"

#include <iostream>
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"

int main() {
    TFile* tf = new TFile("shift.hadd.root");
    TH2F* h2Tpc = (TH2F*)tf->Get("h2NsigPTpc");
    TH3F* h3Tpc = (TH3F*)tf->Get("h2NsigYPtTpc");
    TH2F* h2Tof = (TH2F*)tf->Get("h2NsigPTof");
    TH3F* h3Tof = (TH3F*)tf->Get("h2NsigYPtTof");

    TFile* tfout = new TFile("Shift.root", "recreate");
    tfout->cd();

    // positive side
    ShiftHistMaker* shm_pro = new ShiftHistMaker();
    shm_pro->Init(
        "ProtonShift1D", "Proton Shift;p [GeV/c]", 
        40, 0, 4.0, 
        "ProtonShift2D", "Proton Shift;y;p_{T} [GeV/c]",
        14, -0.7, 0.7,
        40, 0, 4.0
    );
    shm_pro->SetCharge(1);

    // shm_pro->Calc1DHist(h2Tpc);
    // shm_pro->Calc2DHist(h3Tpc);
    shm_pro->Calc1DHist(h2Tof);
    shm_pro->Calc2DHist(h3Tof);

    shm_pro->Get1DHist()->Write();
    shm_pro->Get2DHist()->Write();

    // negative side
    ShiftHistMaker* shm_pbar = new ShiftHistMaker();
    shm_pbar->Init(
        "AntiprotonShift1D", "Antiproton Shift;p [GeV/c]", 
        40, 0, 4.0, 
        "AntiprotonShift2D", "Antiproton Shift;y;p_{T} [GeV/c]",
        14, -0.7, 0.7,
        40, 0, 4.0
    );
    shm_pbar->SetCharge(-1);

    // shm_pbar->Calc1DHist(h2Tpc);
    // shm_pbar->Calc2DHist(h3Tpc);
    shm_pbar->Calc1DHist(h2Tof);
    shm_pbar->Calc2DHist(h3Tof);

    shm_pbar->Get1DHist()->Write();
    shm_pbar->Get2DHist()->Write();

    tfout->Save();

    return 0;

}