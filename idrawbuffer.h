#ifndef I_DRAW_BUFFER_H
#define I_DRAW_BUFFER_H

#include "bufferstate.h"

namespace MyGraphicsOutput
{
class IDrawBuffer
{
public:
    virtual void Resize(int width, int height) = 0;
    virtual bool GetBufferToDraw(RGBpixel** target) = 0;
    virtual void MarkBufferDrawn(RGBpixel** buffer) = 0;
    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;
    virtual bool QuitRequested() = 0;
    virtual void RequestQuit() = 0;
    virtual bool WaitToFillBothBuffers() = 0;


};

} // namespace MyGraphicsOutput
#endif // I_DRAW_BUFFER_H
