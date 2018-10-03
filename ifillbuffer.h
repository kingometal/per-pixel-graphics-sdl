#ifndef I_FILL_BUFFER_H
#define I_FILL_BUFFER_H

#include "bufferstate.h"

namespace MyGraphicsOutput
{
class IFillBuffer
{
public:
    virtual bool GetBufferToFill(RGBpixel** target) = 0;
    virtual void MarkBufferFilled(RGBpixel** buffer) = 0;
    virtual bool QuitRequested() = 0;
    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;
};

} // namespace MyGraphicsOutput
#endif // I_FILL_BUFFER_H
