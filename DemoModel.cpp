#include "DemoModel.h"
#include "Data/RGBData.h"
#include "Interfaces/IPresenter.h"
#include <iostream>

namespace
{
RGBData GetRGBData(int x, int y, int Counter)
{
    return RGBData((x+Counter)%255,Counter % 255,(y + Counter) % 255,255);
}
}

DemoModel::DemoModel(int width, int height, IPresenter& presenter)
    : Counter(0)
    , Width(width)
    , Height(height)
    , Presenter(presenter)
{
    Presenter.Init(height, width, false);
}

DemoModel::~DemoModel()
{
}

void DemoModel::Iterate()
{
    Counter = Counter >= 255?0:Counter+1;
    for (int x = 0; x < Width; ++x)
    {
        for (int y = 0; y < Height; ++y)
        {
            Presenter.StoreRGBData(x,y, GetRGBData(x,y, Counter));
        }
    }
    Presenter.Present();
}

bool DemoModel::ItStopRequested()
{
    return Presenter.QuitRequested();
}
