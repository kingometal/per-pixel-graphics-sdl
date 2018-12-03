#include "DrawJob.h"
#include "DemoModel.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int main(int argc, char** argv)
{
    DemoModel* model = new DemoModel();
    MyGraphicsOutput::DrawJob(SCREEN_WIDTH, SCREEN_HEIGHT, model);
    delete model;
    return 0;
}
