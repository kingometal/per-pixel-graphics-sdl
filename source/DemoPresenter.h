#ifndef DEMO_PRESENTER_H
#define DEMO_PRESENTER_H
#include "Interfaces/IPresenter.h"

class DemoPresenter: public IPresenter
{
public:
    DemoPresenter();
    ~DemoPresenter();

    // IPresenter interface
    void StoreRGBData(int x, int y, const RGBData &data);
    void Present();
    void Init(int height, int width, bool resizable);
private:
    class DemoPresenterImpl;
    DemoPresenterImpl* Pimpl;
};

#endif // DEMO_PRESENTER_H
