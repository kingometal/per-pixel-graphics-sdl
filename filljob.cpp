#include "filljob.h"
#include "ifillbuffer.h"
#include <unistd.h>

int MyGraphicsOutput::FillJob(void* arg)
{
    IFillBuffer* data = static_cast<IFillBuffer*>(arg);
    RGBpixel* pixelDataBuffer = NULL;
    int width;
    int height;
    int indexx;
    int index;
    int counter = 0;
    while(!data->QuitRequested())
    {
        if (!data->GetBufferToFill(&pixelDataBuffer))
        {
            continue; // Both buffers are not drawn yet.
        }

        width = data->GetWidth();
        height = data->GetHeight();
        double secondsCounter = (counter++)/((double) 100);
        for (unsigned int x = 0; x < width; x++)
        {
            indexx = x*height;
            for (unsigned int y = 0; y < height; y++)
            {
                index = indexx + y;
                pixelDataBuffer[index].r = ((int)(secondsCounter*255)+x)%255;
                pixelDataBuffer[index].g = ((int)(secondsCounter*255)+y)%255;
                pixelDataBuffer[index].b = ((int)(secondsCounter*255)%255);
            }
        }
        secondsCounter = 0.0;

        data->MarkBufferFilled(&pixelDataBuffer);
        pixelDataBuffer = NULL;

        usleep(500);
    }
}
