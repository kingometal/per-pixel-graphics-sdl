#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

void run(int width, int height)
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        SDL_Window* gWindow = SDL_CreateWindow( "Simple lightweight per-pixel drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //            SDL_Renderer* renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            SDL_Renderer* renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
            if (NULL == renderer)
            {
                printf( "Can not get surface! SDL_Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Main loop flag
                bool quit = false;
                //Event handler
                SDL_Event e;

                unsigned int framecount = 0;
                double secondsCounter = SDL_GetPerformanceCounter()/(double) SDL_GetPerformanceFrequency();
                double lastFPSOutputTime = secondsCounter;
                // Main Loop
                while( !quit )
                {
                    secondsCounter = SDL_GetPerformanceCounter()/(double) SDL_GetPerformanceFrequency();
                    ++framecount;
                    // Handle user input
                    while( SDL_PollEvent( &e ) != 0)
                    {
                        if ((SDL_QUIT == e.type || (SDL_KEYDOWN == e.type && SDLK_q == e.key.keysym.sym) ))
                        {
                            quit = true;
                        }
                        else if (SDL_WINDOWEVENT == e.type && e.window.event == SDL_WINDOWEVENT_RESIZED)
                        {
                                SDL_GetWindowSize(gWindow, &width, &height);
                                std::cout << "width :"  << width << "height: " << height << std::endl;

                        }

                        if(SDL_KEYDOWN == e.type)
                        {
                            // FPS output
                            std::cout <<  "FPS: " << framecount/(secondsCounter - lastFPSOutputTime) << std::endl;
                            lastFPSOutputTime = secondsCounter;
                            framecount = 0;
                        }
                    }
                    // Fill Surface
                    for (unsigned int x = 0; x < width; x++)
                    {
                        for (unsigned int y = 0; y < height; y++)
                        {
                            SDL_SetRenderDrawColor(renderer, ((int)(secondsCounter*255))%255, (y+(int)(secondsCounter*255))%255, (x+(int)(secondsCounter*255))%255, 255);
                            SDL_RenderDrawPoint(renderer, x, y);
                        }
                    }
                    //Update the window, but not more often than the maximum frames per seconds (FPS)
                    SDL_RenderPresent(renderer);
                } // End main loop
                SDL_DestroyRenderer(renderer);
                renderer = NULL;
            }
            SDL_DestroyWindow( gWindow );
            gWindow = NULL;
        }
        SDL_Quit();
    }
}

int main(int argc, char** argv) 
{
    run(SCREEN_WIDTH, SCREEN_HEIGHT);
    return 0;
}
