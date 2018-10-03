#ifndef VIEWBUFFER_H
#define VIEWBUFFER_H
#include "bufferstate.h"

namespace MyGraphicsOutput
{
class ViewBuffer
{
public:
    ViewBuffer(int width, int height);
    ~ViewBuffer();
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
    bool StartLog;
private:
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
#endif // VIEWBUFFER_H
