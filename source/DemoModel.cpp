#include "DemoModel.h"
#include "Data/RGBData.h"
#include "Interfaces/IPresenter.h"
#include <iostream>
#include <cmath>

namespace {
class ModelDataProvider
{
public:
    ModelDataProvider() = default;
    virtual RGBData GetRGBData(int x, int y, int counter) = 0;
};

class WaveModelDataProvider: public ModelDataProvider
{
public:
    WaveModelDataProvider()
    {
        std::cout << "creating wave model" << std::endl;
    }
    RGBData GetRGBData(int x, int y, int counter)
    {
        double RAmplitude = 1 + sin(sqrt(x*x + y*y)*0.1 - counter);
        return RGBData(RAmplitude * 127, RAmplitude * 127, RAmplitude * 127, RAmplitude * 127);
    }
};

class DefaultModelDataProvider: public ModelDataProvider
{
public:
    DefaultModelDataProvider()
    {
        std::cout << "creating default model" << std::endl;
    }
    RGBData GetRGBData(int x, int y, int counter)
    {
        return RGBData((x+counter)%255, counter % 255, (y+counter) % 255, 255);
    }
};
}

class DemoModel::ModelImpl{
public:
    ModelImpl(int width, int height, IPresenter& presenter, DemoModel::ModelType type)
        : Counter(0)
        , Width(width)
        , Height(height)
        , Presenter(presenter)
        , DataProvider(NULL)
    {
        switch (type)
        {
        case DemoModel::Default:
            DataProvider = new DefaultModelDataProvider();
            break;
        case DemoModel::Waves:
            DataProvider = new WaveModelDataProvider();
            break;
        }
        Presenter.Init(height, width, false);
    }

    ~ModelImpl()
    {
        delete DataProvider;
    }

    void Iterate()
    {
        Counter = Counter >= 255?0:Counter+1;
        for (int x = 0; x < Width; ++x)
        {
            for (int y = 0; y < Height; ++y)
            {
                Presenter.StoreRGBData(x,y, DataProvider->GetRGBData(x, y, Counter));
            }
        }
        Presenter.Present();
    }

    ModelDataProvider* DataProvider;
    int Counter;
    int Width;
    int Height;
    IPresenter& Presenter;
};

DemoModel::DemoModel(int width, int height, IPresenter& presenter, ModelType type)
    : Pimpl(new ModelImpl(width, height, presenter, type))
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
