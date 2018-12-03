#ifndef IMODEL_H
#define IMODEL_H

#include "KeyCodes.h"
#include "RGBData.h"

class IModel
{
public:
    IModel() = default;
    virtual ~IModel() = default;

    virtual bool Resizable() = 0;
    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;
    virtual bool GetBinaryData(int x, int y) = 0;
    virtual RGBData GetRGBData(int x, int y) = 0;
    virtual bool Resize(int width, int height) = 0;

    virtual void Iterate() = 0;
    virtual void KeyPressed(KeyCode key) = 0;
};

#endif // IMODEL_H
