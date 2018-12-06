#include "DemoModel.h"
#include "RandomWalkModel.h"
#include "DemoPresenter.h"
#include "BallModel.h"
#include "UserInput.h"
#include <cstring>
#include <iostream>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int main(int argc, char** argv)
{
    DemoPresenter* presenter = new DemoPresenter();
    UserInput* userInput = new UserInput();
    IModel* model = NULL;
    if (argc == 1) // default
    {
        model = new DemoModel(SCREEN_WIDTH, SCREEN_HEIGHT, *presenter, DemoModel::ModelType::Default);
    }
    else if (argc == 2 && strcmp(argv[1], "randomwalk") == 0)
    {
        model = new RandomWalkModel(SCREEN_WIDTH, SCREEN_HEIGHT, *presenter);
    }
    else if (argc == 2 && strcmp(argv[1], "waves") == 0)
    {
        model = new DemoModel(SCREEN_WIDTH, SCREEN_HEIGHT, *presenter, DemoModel::ModelType::Waves);
    }
    else if (argc == 2 && strcmp(argv[1], "ball") == 0)
    {
        model = new BallModel(SCREEN_WIDTH, SCREEN_HEIGHT, *presenter);
    }

    if (model != NULL)
    {
        while (! userInput->IsQuitRequested())
        {
            model->Iterate();
        }
    }
    delete model;
    delete userInput;
    delete presenter;
    return 0;
}
