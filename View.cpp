#include "View.h"
#include "ViewBuffer.h"
#include <SDL2/SDL.h>
#include "drawjob.h"
#include "filljob.h"

MyGraphicsOutput::View::View()
{
}

MyGraphicsOutput::View::~View()
{
}

void MyGraphicsOutput::View::Start(int initialWidth, int initialHeight)
{
    SDL_Thread *drawThread;
    SDL_Thread *calculateThread;
    int drawThreadReturnValue;
    ViewBuffer* data = new ViewBuffer(initialWidth, initialHeight);

    calculateThread = SDL_CreateThread(FillJob, "calc thread", &data->GetFillBuffer());
    drawThread = SDL_CreateThread(DrawJob, "draw thread", &data->GetDrawBuffer());

    SDL_WaitThread(drawThread, &drawThreadReturnValue);
    drawThread = NULL;
    SDL_WaitThread(calculateThread, &drawThreadReturnValue);
    calculateThread = NULL;
    delete data;
}
