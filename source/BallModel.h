#ifndef BALLMODEL_H
#define BALLMODEL_H
#include "Interfaces/IModel.h"


class IPresenter;


class BallModel : public IModel
{
public:
    BallModel(int width, int height, IPresenter& presenter);
    ~BallModel();
    void Iterate();
private:
    class Ball;
    int Width;
    int Height;
    IPresenter& Presenter;
    int NumBalls;
    Ball** Balls;
    long long LastUpdate;
};

#endif // BALLMODEL_H
