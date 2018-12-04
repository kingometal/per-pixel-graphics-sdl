#include "DemoModel.h"
#include "DemoPresenter.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int main(int argc, char** argv)
{
    DemoPresenter* presenter = new DemoPresenter();
    DemoModel* model = new DemoModel(SCREEN_WIDTH, SCREEN_HEIGHT, *presenter);
    while (! model->ItStopRequested())
    {
        model->Iterate();
    }
    delete model;
    delete presenter;
    return 0;
}
