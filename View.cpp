#include "View.h"
#include "ViewBuffer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;

namespace MyGraphicsOutput
{
int FillJob(void* arg);
int DrawJob(void* arg);
}

namespace
{
void PrintRendererInfo(SDL_Renderer *renderer)
{
    int numdrivers = SDL_GetNumRenderDrivers ();
    cout << "Render driver count: " << numdrivers << endl;
    for (int i=0; i<numdrivers; i++) {
        SDL_RendererInfo drinfo;
        SDL_GetRenderDriverInfo (i, &drinfo);
        cout << "Driver name ("<<i<<"): " << drinfo.name << endl;
        if (drinfo.flags & SDL_RENDERER_SOFTWARE) cout << " the renderer is  a software fallback" << endl;
        if (drinfo.flags & SDL_RENDERER_ACCELERATED) cout << " the renderer  uses hardware acceleration" << endl;
        if (drinfo.flags & SDL_RENDERER_PRESENTVSYNC) cout << " present is synchronized with the refresh rate" << endl;
        if (drinfo.flags & SDL_RENDERER_TARGETTEXTURE) cout << " the  renderer supports rendering to texture" << endl;
    }

    SDL_RendererInfo drinfo;
    SDL_GetRendererInfo (renderer, &drinfo);
    cout << "Current Driver name " << drinfo.name << endl;
    if (drinfo.flags & SDL_RENDERER_SOFTWARE) cout << " the renderer is  a software fallback" << endl;
    if (drinfo.flags & SDL_RENDERER_ACCELERATED) cout << " the renderer  uses hardware acceleration" << endl;
    if (drinfo.flags & SDL_RENDERER_PRESENTVSYNC) cout << " present is synchronized with the refresh rate" << endl;
    if (drinfo.flags & SDL_RENDERER_TARGETTEXTURE) cout << " the  renderer supports rendering to texture" << endl;
}

bool Init(SDL_Window** window, SDL_Renderer **renderer, TTF_Font** font, int width, int height)
{
    bool success = false;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        if (0 > TTF_Init())
        {
            printf( "TTF could not initialize! TTF_Error: %s\n", TTF_GetError() );
        }
        else
        {
            *font = TTF_OpenFont("FreeMono.ttf", 24); //this opens a font style and sets a size
            if (NULL == *font)
            {
                std::cout << "can not create font" << std::endl;
                std::cout << TTF_GetError() << std::endl;
            }
            else
            {
                *window = SDL_CreateWindow( "Simple lightweight per-pixel drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
                if( window == NULL )
                {
                    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
                }
                else
                {
                    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);
                    //                    *renderer = SDL_CreateRenderer(*window, -1, 0);
                    if (NULL == renderer)
                    {
                        printf( "Can not get surface! SDL_Error: %s\n", SDL_GetError() );
                    }
                    else
                    {
                        success = true;
                    }
                }
            }
        }
    }
    return success;
}

void DeInit(SDL_Window** window, SDL_Renderer **renderer, TTF_Font** font)
{
    TTF_CloseFont(*font);
    TTF_Quit();
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow( *window );
    SDL_Quit();
}

void PrintText(SDL_Renderer* renderer, const char* text, SDL_Color& color, TTF_Font* font, int x, int y)
{
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
    if (surfaceMessage)
    {
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
        if (Message)
        {
            SDL_Rect Message_rect; //create a rect
            Message_rect.x = x;  //controls the rect's x coordinate
            Message_rect.y = y; // controls the rect's y coordinte
            Message_rect.w = surfaceMessage->w; // controls the width of the rect
            Message_rect.h = surfaceMessage->h; // controls the height of the rect

            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
            SDL_DestroyTexture(Message);
        }
        SDL_FreeSurface(surfaceMessage);
    }
}
} // anonymous namespace



int MyGraphicsOutput::FillJob(void* arg)
{
    ViewBuffer* data = (ViewBuffer*) arg;
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
        if (data->StartLog) cout << "w/h: " << width << " / " << height << endl;
        for (unsigned int x = 0; x < width; x++)
        {
//            if (data->StartLog) cout << "x : " << x << " ";
            for (unsigned int y = 0; y < height; y++)
            {
//                if (data->StartLog) cout << "y : " << y << endl;
                pixelDataBuffer[x*height + y].r = ((int)(secondsCounter*255)+x)%255;
                pixelDataBuffer[x*height + y].g = ((int)(secondsCounter*255)+y)%255;
                pixelDataBuffer[x*height + y].b = ((int)(secondsCounter*255)%255);
            }
        }
        if (data->StartLog) cout << "filled w/h: " << width << " / " << height << endl;
        secondsCounter = 0.0;

        data->MarkBufferFilled(&pixelDataBuffer);
        pixelDataBuffer = NULL;
        SDL_Delay(1);
    }
}

int MyGraphicsOutput::DrawJob(void* arg)
{
    ViewBuffer* data = (ViewBuffer*) arg;
    int width = data->GetWidth();
    int height = data->GetHeight();
    SDL_Window* gWindow = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    if (Init(&gWindow, &renderer, &font, width, height))
    {
        SDL_Event e;
        unsigned int framecount = 0;
        double secondsCounter = SDL_GetPerformanceCounter()/(double) SDL_GetPerformanceFrequency();
        double lastFPSOutputTime = secondsCounter;
        SDL_Color fontColor = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
        RGBpixel* pixelDataBuffer = NULL;

        // Main Loop
        while( !data->QuitRequested() )
        {
            if (data->StartLog) cout << "DrawJob" << endl;
            secondsCounter = SDL_GetPerformanceCounter()/(double) SDL_GetPerformanceFrequency();

            // Handle user input
            while( SDL_PollEvent( &e ) != 0)
            {
                if (data->StartLog) cout << "GotEvent" << endl;

                if ((SDL_QUIT == e.type || (SDL_KEYDOWN == e.type && SDLK_q == e.key.keysym.sym) ))
                {
                    data->RequestQuit();
                }
                else if (SDL_WINDOWEVENT == e.type && e.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    data->StartLog = true;
                    data->WaitToFillBothBuffers();
                    SDL_GetWindowSize(gWindow, &width, &height);
                    std::cout << "RESIZE:    width :"  << width << " height: " << height << std::endl;
                    SDL_DestroyRenderer(renderer);
                    renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
                    data->Resize(width, height);
                }
            }

            if (data->StartLog) cout << "DrawJob1" << endl;
            width = data->GetWidth();
            height = data->GetHeight();


            if(!data->GetBufferToDraw(&pixelDataBuffer))
            {
                continue; // No new data to show.
            }
            if (data->StartLog) cout << "DrawJob2" << endl;

            // Fill Surface
            int indexx = 0;
            for (unsigned int x = 0; x < width; x++)
            {
                indexx = x*height;
                for (unsigned int y = 0; y < height; y++)
                {
                    int index = indexx + y;
                    SDL_SetRenderDrawColor(renderer, pixelDataBuffer[index].r, pixelDataBuffer[index].g, pixelDataBuffer[index].b, 255);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }

            PrintText(renderer, std::to_string(framecount/(secondsCounter - lastFPSOutputTime)).c_str(), fontColor, font, 0,0 );


            if (data->StartLog) cout << "DrawJob8" << endl;
            // reset FPS counter
            if (secondsCounter - lastFPSOutputTime > 1.0)
            {
                lastFPSOutputTime = secondsCounter;
                framecount = 0;
            }
            ++framecount;
            if (data->StartLog) cout << "Start RenderPresent" << endl;

            //Update the window
            SDL_RenderPresent(renderer);
            if (data->StartLog) cout << "Finish RenderPresent" << endl;

            data->MarkBufferDrawn(&pixelDataBuffer);
            pixelDataBuffer = NULL;

        } // End main loop
    }
    DeInit(&gWindow, &renderer, &font);
    return 0;
}



MyGraphicsOutput::View::View(int width, int height)
    : W(width)
    , H(height)
{

}

MyGraphicsOutput::View::~View()
{

}

void MyGraphicsOutput::View::Start()
{
    SDL_Thread *drawThread;
    SDL_Thread *calculateThread;
    int drawThreadReturnValue;
    ViewBuffer* data = new ViewBuffer(W, H);

    calculateThread = SDL_CreateThread(FillJob, "calc thread", (void*) data);
    drawThread = SDL_CreateThread(DrawJob, "draw thread", (void*) data);

    SDL_WaitThread(drawThread, &drawThreadReturnValue);
    drawThread = NULL;
    SDL_WaitThread(calculateThread, &drawThreadReturnValue);
    calculateThread = NULL;
    delete data;
}
