#include "ViewBuffer.h"
#include "idrawbuffer.h"
#include "ifillbuffer.h"

#include <stdlib.h>
#include <iostream>

using namespace MyGraphicsOutput;
using namespace std;

namespace MyGraphicsOutput{
class ViewBufferImpl: public IDrawBuffer, public IFillBuffer
{
public:
    ViewBufferImpl(int width, int height);
    ~ViewBufferImpl();

    void Resize(int width, int height);
    bool GetBufferToDraw(RGBpixel** target);
    void MarkBufferDrawn(RGBpixel** buffer);
    bool GetBufferToFill(RGBpixel** target);
    void MarkBufferFilled(RGBpixel** buffer);
    bool QuitRequested();
    void RequestQuit();
    bool WaitToFillBothBuffers();
    int GetWidth();
    int GetHeight();

    int Width;
    int Height;
    bool Quit;
    int PixelCount;
    RGBpixel* PixelDataBuffer1;
    RGBpixel* PixelDataBuffer2;
    BufferState FirstPartState = DRAWN;
    BufferState SecondPartState = DRAWN;
};
}

ViewBufferImpl::ViewBufferImpl(int width, int height)
    : Width(width)
    , Height(height)
    , PixelCount(width*height)
    , PixelDataBuffer1((RGBpixel*) malloc((int) sizeof(RGBpixel)*PixelCount))
    , PixelDataBuffer2((RGBpixel*) malloc((int) sizeof(RGBpixel)*PixelCount))
    , Quit(false)
{
}

ViewBufferImpl::~ViewBufferImpl()
{

}

void ViewBufferImpl::Resize(int width, int height)
{
    delete PixelDataBuffer2;
    PixelDataBuffer2 = NULL;
    delete PixelDataBuffer1;
    PixelDataBuffer1 = NULL;
    Height = height;
    Width = width;
    PixelCount = width*height;
    PixelDataBuffer1 = (RGBpixel*) malloc((int) sizeof(RGBpixel)*PixelCount);
    PixelDataBuffer2 = (RGBpixel*) malloc((int) sizeof(RGBpixel)*PixelCount);
    for (int i = 0; i < PixelCount; i++)
    {
        PixelDataBuffer1[i].r = 0;
        PixelDataBuffer1[i].g = 0;
        PixelDataBuffer1[i].b = 0;
        PixelDataBuffer2[i].r = 0;
        PixelDataBuffer2[i].g = 0;
        PixelDataBuffer2[i].b = 0;
    }
    FirstPartState = DRAWN;
    SecondPartState = DRAWN;
}

bool ViewBufferImpl::GetBufferToDraw(MyGraphicsOutput::RGBpixel **target)
{
    bool success = false;
    if (target != NULL)
    {
        if (FirstPartState == FILLED_NOT_DRAWN)
        {
            *target = PixelDataBuffer1;
            FirstPartState = DRAWING;
            success = true;
        }
        else if (SecondPartState == FILLED_NOT_DRAWN)
        {
            *target = PixelDataBuffer2;
            SecondPartState = DRAWING;
            success = true;
        }
        else
        {
            *target = NULL;
        }
    }
    return success;
}

void ViewBufferImpl::MarkBufferDrawn(MyGraphicsOutput::RGBpixel **buffer)
{
    if (*buffer == PixelDataBuffer1)
    {
       FirstPartState = DRAWN;
    }
    else
    {
        SecondPartState = DRAWN;
    }
}

bool ViewBufferImpl::GetBufferToFill(MyGraphicsOutput::RGBpixel **target)
{
    bool success = false;

    if (FirstPartState == DRAWN)
    {
        *target = PixelDataBuffer1;
        FirstPartState = FILLING;
        success = true;
    }
    else if (SecondPartState == DRAWN)
    {
        *target = PixelDataBuffer2;
        SecondPartState = FILLING;
        success = true;
    }
    else
    {
        *target = NULL;
    }
    return success;
}

void ViewBufferImpl::MarkBufferFilled(MyGraphicsOutput::RGBpixel **buffer)
{
    if (*buffer == PixelDataBuffer2)
    {
        SecondPartState = FILLED_NOT_DRAWN;
    }
    else
    {
       FirstPartState = FILLED_NOT_DRAWN;
    }
}

bool ViewBufferImpl::QuitRequested()
{
    return Quit;
}

void ViewBufferImpl::RequestQuit()
{
    Quit = true;
}

bool ViewBufferImpl::WaitToFillBothBuffers()
{
    while (true)
    {
        if (FirstPartState == FILLED_NOT_DRAWN && SecondPartState == FILLED_NOT_DRAWN)
            break;
    }
    FirstPartState = HOLD;
    SecondPartState = HOLD;
}

int ViewBufferImpl::GetWidth()
{
    return Width;
}

int ViewBufferImpl::GetHeight()
{
    return Height;
}

ViewBuffer::ViewBuffer(int width, int height)
    : pimpl(new ViewBufferImpl(width, height))
{

}

ViewBuffer::~ViewBuffer()
{
    delete pimpl;
    pimpl = NULL;
}

IDrawBuffer &ViewBuffer::GetDrawBuffer()
{
    return *pimpl;
}

IFillBuffer &ViewBuffer::GetFillBuffer()
{
    return *pimpl;
}
