#ifndef DEMOMODEL_H
#define DEMOMODEL_H
#include "Interfaces/IModel.h"
class IPresenter;

class DemoModel: public IModel
{
public:
    enum ModelType
    {
        Default,
        Waves
    };
    DemoModel(int width, int height, IPresenter &presenter, ModelType type);
    ~DemoModel();

    void Iterate();
private:
    class ModelImpl;
    ModelImpl* Pimpl;
};

#endif // DEMOMODEL_H
