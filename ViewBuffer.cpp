#include "ViewBuffer.h"
#include <stdlib.h>
#include <iostream>

using namespace MyGraphicsOutput;
using namespace std;

ViewBuffer::ViewBuffer(int width, int height)
    : Width(width)
    , Height(height)
    , PixelCount(width*height)
    , PixelDataBuffer1((RGBpixel*) malloc((int) sizeof(RGBpixel)*PixelCount))
    , PixelDataBuffer2((RGBpixel*) malloc((int) sizeof(RGBpixel)*PixelCount))
    , Quit(false)
    , StartLog(false)
{
}

ViewBuffer::~ViewBuffer()
{

}

void ViewBuffer::Resize(int width, int height)
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
    if (StartLog) cout << "releasing first part" << endl;
    FirstPartState = DRAWN;
    if (StartLog) cout << "releasing second part" << endl;
    SecondPartState = DRAWN;
    if (StartLog) cout << "released both parts" << endl;
}

bool ViewBuffer::GetBufferToDraw(MyGraphicsOutput::RGBpixel **target)
{
    if (StartLog) cout << "GetBufferToDraw started" << endl;
    bool success = false;
    if (target != NULL)
    {
        if (FirstPartState == FILLED_NOT_DRAWN)
        {
            *target = PixelDataBuffer1;
            FirstPartState = DRAWING;
            success = true;
            if (StartLog) cout << "draw the first part" << " w " << Width << " h " << Height << endl;
        }
        else if (SecondPartState == FILLED_NOT_DRAWN)
        {
            *target = PixelDataBuffer2;
            SecondPartState = DRAWING;
            success = true;
            if (StartLog) cout << "draw the second part" << " w " << Width << " h " << Height << endl;
        }
        else
        {
            *target = NULL;
        }
    }
    if (StartLog) cout << "GetBufferToDraw finished" << endl;
    return success;
}

void ViewBuffer::MarkBufferDrawn(MyGraphicsOutput::RGBpixel **buffer)
{
    if (*buffer == PixelDataBuffer1)
    {
       if (StartLog) cout << "finish draw the first part" << endl;
       FirstPartState = DRAWN;
    }
    else
    {
        if (StartLog) cout << "finish draw the second part" << endl;
        SecondPartState = DRAWN;
    }
}

bool ViewBuffer::GetBufferToFill(MyGraphicsOutput::RGBpixel **target)
{
//    if (StartLog) cout << "GetBufferToFill started" << endl;
    bool success = false;

    if (FirstPartState == DRAWN)
    {
        if (StartLog) cout << "fill the first part" << endl;
        *target = PixelDataBuffer1;
        FirstPartState = FILLING;
        success = true;
    }
    else if (SecondPartState == DRAWN)
    {
        if (StartLog) cout << "fill the second part" << endl;
        *target = PixelDataBuffer2;
        SecondPartState = FILLING;
        success = true;
    }
    else
    {
        *target = NULL;
    }
    if (StartLog && success) cout << "Got Buffer To Fill" << endl;
    return success;
}

void ViewBuffer::MarkBufferFilled(MyGraphicsOutput::RGBpixel **buffer)
{
    if (*buffer == PixelDataBuffer2)
    {
        if (StartLog) cout << "finish fill the second part" << endl;
        SecondPartState = FILLED_NOT_DRAWN;
    }
    else
    {
       if (StartLog) cout << "finish fill the first part" << endl;
       FirstPartState = FILLED_NOT_DRAWN;
    }
}

bool ViewBuffer::QuitRequested()
{
    return Quit;
}

void ViewBuffer::RequestQuit()
{
    Quit = true;
}

bool ViewBuffer::WaitToFillBothBuffers()
{
    if (StartLog) cout << "WaitToFillBothBuffers started" << endl;
    while (true)
    {
        if (FirstPartState == FILLED_NOT_DRAWN && SecondPartState == FILLED_NOT_DRAWN)
            break;
    }
    if (StartLog) cout << "WaitToFillBothBuffers finished" << endl;
    FirstPartState = HOLD;
    SecondPartState = HOLD;
}

int ViewBuffer::GetWidth()
{
    return Width;
}

int ViewBuffer::GetHeight()
{
    return Height;
}
