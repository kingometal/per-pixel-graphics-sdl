#include "DemoModel.h"


DemoModel::DemoModel()
    : Counter(0)
{
}

DemoModel::~DemoModel()
{
}

bool DemoModel::Resizable()
{
    return false;
}

int DemoModel::GetWidth()
{
}

int DemoModel::GetHeight()
{
}

bool DemoModel::GetBinaryData(int x, int y)
{
}

RGBData DemoModel::GetRGBData(int x, int y)
{
    return RGBData((x+Counter)%255,Counter % 255,(y + Counter) % 255,255);
}

void DemoModel::Iterate()
{
    Counter = Counter >= 255?0:Counter+1;
}

void DemoModel::KeyPressed(KeyCode key)
{

}

bool DemoModel::Resize(int width, int height)
{
    return false;
}
