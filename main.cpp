#include "View.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int main(int argc, char** argv)
{
    MyGraphicsOutput::View myView(SCREEN_WIDTH, SCREEN_HEIGHT);
    myView.Start();
    return 0;
}
