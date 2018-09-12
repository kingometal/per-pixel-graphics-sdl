#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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

                // Prepare text output
                if (TTF_Init() < 0)
                {
                    std::cout << TTF_GetError() << std::endl;
                }
                else
                {
                    SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
                    TTF_Font* font = TTF_OpenFont("FreeMono.ttf", 24); //this opens a font style and sets a size
                    if (NULL == font)
                    {
                        std::cout << "can not create font" << std::endl;
                        std::cout << TTF_GetError() << std::endl;
                    }
                    else
                    {

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

                            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, std::to_string(framecount/(secondsCounter - lastFPSOutputTime)).c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
                            if (surfaceMessage)
                            {
                                SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
                                if (Message)
                                {
                                    SDL_Rect Message_rect; //create a rect
                                    Message_rect.x = 0;  //controls the rect's x coordinate
                                    Message_rect.y = 0; // controls the rect's y coordinte
                                    Message_rect.w = surfaceMessage->w; // controls the width of the rect
                                    Message_rect.h = surfaceMessage->h; // controls the height of the rect

                                    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
                                    SDL_DestroyTexture(Message);
                                }
                                SDL_FreeSurface(surfaceMessage);
                            }
                            if (secondsCounter - lastFPSOutputTime > 1.0)
                            {
                                lastFPSOutputTime = secondsCounter;
                                framecount = 0;
                            }

                            //Update the window
                            SDL_RenderPresent(renderer);
                        } // End main loop
                        TTF_CloseFont(font);
                    }
                    TTF_Quit();
                }
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
