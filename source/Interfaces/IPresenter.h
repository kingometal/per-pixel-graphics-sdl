#ifndef IPRESENTER_H
#define IPRESENTER_H

class RGBData;

class IPresenter
{
public:
    IPresenter() = default;
    ~IPresenter() = default;
    virtual void Init(int height, int width, bool resizable) = 0;
    virtual void StoreRGBData(int x, int y, const RGBData& data) = 0;
    virtual void Present() = 0;
};

#endif // IPRESENTER_H
