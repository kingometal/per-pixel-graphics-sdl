#ifndef DEMOMODEL_H
#define DEMOMODEL_H
#include "Interfaces/IModel.h"

class DemoModel: public IModel
{
public:
    DemoModel();
    ~DemoModel();

    // IModel interface
    bool Resizable();
    bool BinaryDataAvailable();
    bool RGBDataAvailable();
    int GetWidth();
    int GetHeight();
    bool GetBinaryData(int x, int y);
    RGBData GetRGBData(int x, int y);
    void Iterate();
    void KeyPressed(KeyCode key);
    bool Resize(int width, int height);
private:
    int Counter;
};

#endif // DEMOMODEL_H
