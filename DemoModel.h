#ifndef DEMOMODEL_H
#define DEMOMODEL_H
class IPresenter;

class DemoModel
{
public:
    DemoModel(int width, int height, IPresenter &presenter);
    ~DemoModel();

    void Iterate();
private:
    class ModelImpl;
    ModelImpl* Pimpl;
};

#endif // DEMOMODEL_H
