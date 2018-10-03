#ifndef BUFFERSTATE_H
#define BUFFERSTATE_H

namespace MyGraphicsOutput
{
enum BufferState
{
    DRAWING,
    DRAWN,
    FILLING,
    FILLED_NOT_DRAWN,
    HOLD
};

struct RGBpixel
{
    char r;
    char g;
    char b;
};


}
#endif // BUFFERSTATE_H
