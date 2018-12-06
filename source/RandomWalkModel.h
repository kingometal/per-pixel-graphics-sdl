#ifndef RANDOMWALKMODEL_H
#define RANDOMWALKMODEL_H
#include "Interfaces/IModel.h"
class IPresenter;

class RandomWalkModel: public IModel
{
public:
    RandomWalkModel(int width, int height, IPresenter &presenter);
    void Iterate();
private:
    int X;
    int Y;
    int Width;
    int Height;
    int Color;
    int SkipFrames;
    IPresenter& Presenter;
};

#endif // RANDOMWALKMODEL_H
