#ifndef __SFM_HEADER__
#define __SFM_HEADER__


class TF1;
class TH1F;
class TH2F;
class TH3F;

class ShiftFitMaker {

    private:
        TH1F* h1;
        TF1* gaus;

    public:
        ShiftFitMaker(){}
        ~ShiftFitMaker(){}

        void Init();
        void GetProjectionFromTH2(TH2F* h2, double p, int charge);
        void GetProjectionFromTH3(TH3F* h3, double y, double pT, int charge);
        double GetShift();

};

#endif