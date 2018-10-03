#ifndef VIEWBUFFER_H
#define VIEWBUFFER_H

namespace MyGraphicsOutput
{
class ViewBufferImpl;
class IDrawBuffer;
class IFillBuffer;

class ViewBuffer
{
public:
    ViewBuffer(int width, int height);
    ~ViewBuffer();

    IDrawBuffer& GetDrawBuffer();
    IFillBuffer& GetFillBuffer();

private:
   ViewBufferImpl* pimpl;
};
}
#endif // VIEWBUFFER_H
