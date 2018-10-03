#include "filljob.h"
#include "ifillbuffer.h"
#include <SDL2/SDL.h>

int MyGraphicsOutput::FillJob(void* arg)
{
    IFillBuffer* data = static_cast<IFillBuffer*>(arg);
    RGBpixel* pixelDataBuffer = NULL;
    int width;
    int height;
    while(!data->QuitRequested())
    {
        if (!data->GetBufferToFill(&pixelDataBuffer))
        {
            continue; // Both buffers are not drawn yet.
        }

        width = data->GetWidth();
        height = data->GetHeight();
        double secondsCounter = SDL_GetPerformanceCounter()/(double) SDL_GetPerformanceFrequency();
        for (unsigned int x = 0; x < width; x++)
        {
            for (unsigned int y = 0; y < height; y++)
            {
                pixelDataBuffer[x*height + y].r = ((int)(secondsCounter*255)+x)%255;
                pixelDataBuffer[x*height + y].g = ((int)(secondsCounter*255)+y)%255;
                pixelDataBuffer[x*height + y].b = ((int)(secondsCounter*255)%255);
            }
        }
        secondsCounter = 0.0;

        data->MarkBufferFilled(&pixelDataBuffer);
        pixelDataBuffer = NULL;
        SDL_Delay(1);
    }
}
