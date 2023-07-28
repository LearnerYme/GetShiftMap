#ifndef __SHM_HEADER__
#define __SHM_HEADER__

class ShiftFitMaker;
class TH1F;
class TH2F;
class TH3F;

class ShiftHistMaker {

    private:
        TH1F* h1;
        TH2F* h2;
        int charge;
        ShiftFitMaker* sfm;

    public:
        ShiftHistMaker(){}
        ~ShiftHistMaker(){}

        void Init(const char* name1, const char* title1, int nBin1d, double x11d, double x21d, const char* name2, const char* title2, int nBinX2d, double x12d, double x22d, int nBinY2d, double y12d, double y22d);
        void SetCharge(int q);
        void Calc1DHist(TH2F* h2);
        void Calc2DHist(TH3F* h3);
        TH1F* Get1DHist();
        TH2F* Get2DHist();

};

#endif