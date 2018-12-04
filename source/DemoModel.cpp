#include "DemoModel.h"
#include "Data/RGBData.h"
#include "Interfaces/IPresenter.h"
#include <iostream>
#include <cmath>

class DemoModel::ModelImpl{
public:
    ModelImpl(int width, int height, IPresenter& presenter)
        : Counter(0)
        , Width(width)
        , Height(height)
        , Presenter(presenter)
    {
        Presenter.Init(height, width, false);
    }

    RGBData GetRGBData(int x, int y)
    {

	int x2 = (320-x)*(320-x);
	int mx2 = (280-x)*(280-x);
	int y2 = y*y;
	double Amplitude1 = sin(sqrt(x2 + y2)*0.1 - Counter);
        double Amplitude2 = sin(sqrt(mx2 + y2)*0.1 - Counter);
	double RAmplitude = 1.0 + (Amplitude1 + Amplitude2)/2.0;
        return RGBData(RAmplitude * 127, RAmplitude * 127, RAmplitude * 127, RAmplitude * 127);
    }

    void Iterate()
    {
        Counter = Counter >= 255?0:Counter+1;
        for (int x = 0; x < Width; ++x)
        {
            for (int y = 0; y < Height; ++y)
            {
                Presenter.StoreRGBData(x,y, GetRGBData(x,y));
            }
        }
        Presenter.Present();
    }

    int Counter;
    int Width;
    int Height;
    IPresenter& Presenter;
};

DemoModel::DemoModel(int width, int height, IPresenter& presenter)
    : Pimpl(new ModelImpl(width, height, presenter))
{
}

DemoModel::~DemoModel()
{
    delete Pimpl;
}

void DemoModel::Iterate()
{
    Pimpl->Iterate();
}
