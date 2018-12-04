#include "DemoModel.h"
#include "Data/RGBData.h"
#include "Interfaces/IPresenter.h"
#include <iostream>

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
        return RGBData((x+Counter)%255,Counter % 255,(y + Counter) % 255,255);
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
