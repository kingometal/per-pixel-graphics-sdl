#include "DemoModel.h"
#include "RandomWalkModel.h"
#include "DemoPresenter.h"
#include "UserInput.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int main(int argc, char** argv)
{
    DemoPresenter* presenter = new DemoPresenter();
    UserInput* userInput = new UserInput();
    if (argc == 1) // default
    {
        DemoModel* model = new DemoModel(SCREEN_WIDTH, SCREEN_HEIGHT, *presenter, DemoModel::ModelType::Default);
        while (! userInput->IsQuitRequested())
        {
            model->Iterate();
        }
        delete model;
    }
    else
    {
        RandomWalkModel* model = new RandomWalkModel(SCREEN_WIDTH, SCREEN_HEIGHT, *presenter);
        while (! userInput->IsQuitRequested())
        {
            model->Iterate();
        }
        delete model;
    }
    delete userInput;
    delete presenter;
    return 0;
}
