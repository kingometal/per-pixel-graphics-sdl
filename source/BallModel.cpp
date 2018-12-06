#include "BallModel.h"
#include "Interfaces/IPresenter.h"
#include "Data/RGBData.h"
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <iostream>

class BallModel::Ball
{
public:
    Ball(double x, double y, double vx, double vy, double radius)
        : X(x)
        , Y(y)
        , Vx(vx)
        , Vy(vy)
        , Radius(radius)
    {

    }

    void Move(int width, int height)
    {
        X += Vx;
        Y += Vy;
        if (Vx > 0 && X+Radius > width) Vx = -Vx;
        if (Vx < 0 && X-Radius < 0) Vx = -Vx;
        if (Vy > 0 && Y+Radius > height) Vy = -Vy;
        if (Vy < 0 && Y-Radius < 0) Vy = -Vy;
//        Vx += 0.01 * (rand()%2 - 1);
//        Vy += 0.01 * (rand()%2 - 1);
    }

    double X;
    double Y;
private:
    double Vx;
    double Vy;
    double Radius;
};


BallModel::BallModel(int width, int height, IPresenter &presenter)
    : Width(width)
    , Height(height)
    , Presenter(presenter)
    , NumBalls(100)
{
    Balls = new Ball*[NumBalls];
    for (int i = 0; i < NumBalls; i++)
    {
        double angle = (i/(double) NumBalls)*(2*M_PI);
        int x = width/2 + width/3 * cos(angle);
        int y = height/2 + height/3 * sin(angle);
        Balls[i] = new Ball(x, y, 0.5*(2.5 - rand()%5), 0.5*(2.5 - rand()%5), 10);
    }
    Presenter.Init(Width, Height, false);
    LastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

BallModel::~BallModel()
{
    for (int i = 0; i < NumBalls; i++)
    {
        delete Balls[i];
    }
    delete[] Balls;
}

void DrawBall(int x, int y, char color, IPresenter& presenter)
{
    presenter.StoreRGBData(x-2, y-1, RGBData(color,color,color,255));
    presenter.StoreRGBData(x-2, y, RGBData(color,color,color,255));
    presenter.StoreRGBData(x-2, y+1, RGBData(color,color,color,255));
    presenter.StoreRGBData(x-1, y-2, RGBData(color,color,color,255));
    presenter.StoreRGBData(x-1, y-1, RGBData(color,color,color,255));
    presenter.StoreRGBData(x-1, y, RGBData(color,color,color,255));
    presenter.StoreRGBData(x-1, y+1, RGBData(color,color,color,255));
    presenter.StoreRGBData(x-1, y+2, RGBData(color,color,color,255));
    presenter.StoreRGBData(x, y-2, RGBData(color,color,color,255));
    presenter.StoreRGBData(x, y-1, RGBData(color,color,color,255));
    presenter.StoreRGBData(x, y, RGBData(color,color,color,255));
    presenter.StoreRGBData(x, y+1, RGBData(color,color,color,255));
    presenter.StoreRGBData(x, y+2, RGBData(color,color,color,255));
    presenter.StoreRGBData(x+1, y-2, RGBData(color,color,color,255));
    presenter.StoreRGBData(x+1, y-1, RGBData(color,color,color,255));
    presenter.StoreRGBData(x+1, y, RGBData(color,color,color,255));
    presenter.StoreRGBData(x+1, y+1, RGBData(color,color,color,255));
    presenter.StoreRGBData(x+1, y+2, RGBData(color,color,color,255));
    presenter.StoreRGBData(x+2, y-1, RGBData(color,color,color,255));
    presenter.StoreRGBData(x+2, y, RGBData(color,color,color,255));
    presenter.StoreRGBData(x+2, y+1, RGBData(color,color,color,255));
}

void BallModel::Iterate()
{
    for (int i = 0; i < NumBalls ; i ++)
    {
        Ball* ball = Balls[i];
        DrawBall(ball->X, ball->Y, 0, Presenter);
        ball->Move(Width, Height);
        DrawBall(ball->X, ball->Y, 255, Presenter);
    }
    long long currentTime = LastUpdate;
    while (currentTime - LastUpdate < 20)
    {
        currentTime =  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        usleep(100);
    }
    LastUpdate = currentTime;
    Presenter.Present();
}
