#ifndef DEMOMODEL_H
#define DEMOMODEL_H
class IPresenter;

class DemoModel
{
public:
    DemoModel(int width, int height, IPresenter &presenter);
    ~DemoModel();

    void Iterate();
    bool ItStopRequested();
private:
    int Counter;
    int Width;
    int Height;
    IPresenter& Presenter;
};

#endif // DEMOMODEL_H
