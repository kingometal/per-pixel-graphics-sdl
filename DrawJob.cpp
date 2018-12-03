#include "DrawJob.h"
#include "Interfaces/IModel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;


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

bool Init(SDL_Window** window, SDL_Renderer **renderer, TTF_Font** font, int width, int height, bool resizable)
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
                *window = SDL_CreateWindow( "Simple lightweight per-pixel drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | (resizable?SDL_WINDOW_RESIZABLE:0));
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


int MyGraphicsOutput::DrawJob(int initialWidth, int initialHeight, IModel* model)
{
    int width = initialWidth;
    int height = initialHeight;
    int quitRequested = false;
    SDL_Window* gWindow = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    if (Init(&gWindow, &renderer, &font, width, height, model->Resizable()))
    {
        SDL_Event e;
        unsigned int framecount = 0;
        double secondsCounter = SDL_GetPerformanceCounter()/(double) SDL_GetPerformanceFrequency();
        double lastFPSOutputTime = secondsCounter;
        SDL_Color fontColor = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

        // Main Loop
        while( !quitRequested )
        {
            secondsCounter = SDL_GetPerformanceCounter()/(double) SDL_GetPerformanceFrequency();

            // Handle user input
            while( SDL_PollEvent( &e ) != 0)
            {
                if ((SDL_QUIT == e.type || (SDL_KEYDOWN == e.type && SDLK_q == e.key.keysym.sym) ))
                {
                    quitRequested = true;
                }
                else if (SDL_WINDOWEVENT == e.type && e.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    SDL_GetWindowSize(gWindow, &width, &height);
                    std::cout << "RESIZE:    width :"  << width << " height: " << height << std::endl;
                    SDL_DestroyRenderer(renderer);
                    renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
                    model->Resize(width, height);
                }
            }

            // Fill Surface
            for (unsigned int x = 0; x < width; x++)
            {
                for (unsigned int y = 0; y < height; y++)
                {
                    RGBData rgbData = model->GetRGBData(x,y);
                    SDL_SetRenderDrawColor(renderer, rgbData.R, rgbData.G, rgbData.B, rgbData.Brightness);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
            PrintText(renderer, std::to_string(framecount/(secondsCounter - lastFPSOutputTime)).c_str(), fontColor, font, 0,0 );

            // reset FPS counter
            if (secondsCounter - lastFPSOutputTime > 1.0)
            {
                lastFPSOutputTime = secondsCounter;
                framecount = 0;
            }
            ++framecount;

            //Update the window
            SDL_RenderPresent(renderer);
            model->Iterate();
        } // End main loop
    }
    DeInit(&gWindow, &renderer, &font);
    return 0;
}
