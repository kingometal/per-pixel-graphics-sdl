#include "RandomWalkModel.h"
#include "Interfaces/IPresenter.h"
#include "Data/RGBData.h"
#include <cstdlib>

RandomWalkModel::RandomWalkModel(int width, int height, IPresenter &presenter)
    : X(width/2)
    , Y(height/2)
    , Width(width)
    , Height(height)
    , Color(0)
    , SkipFrames(0)
    , Presenter(presenter)
{
    Presenter.Init(height, width, false);
}

void RandomWalkModel::Iterate()
{
    int randomNumber = rand()%4;
    if (randomNumber == 0)
    {
        X = (X + 1) % Width;
    }
    else if (randomNumber == 1)
    {
        Y = (Y+1) % Height;
    }
    else if (randomNumber == 2)
    {
        X = (X+Width - 1)% Width;
    }
    else
    {
        Y = (Y+Height - 1) % Height;
    }
    Color = (Color + 1) % 255;
    RGBData color (Color, Color, Color, 255);
    Presenter.StoreRGBData(X, Y, color);
    if (SkipFrames++ > 1000)
    {
        SkipFrames = 0;
        Presenter.Present();
    }
}
