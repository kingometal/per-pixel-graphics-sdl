#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int main(int argc, char** argv) 
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        SDL_Window* gWindow = SDL_CreateWindow( "Simple lightweight per-pixel drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            SDL_Surface* gScreenSurface = SDL_GetWindowSurface( gWindow );

            if (NULL == gScreenSurface)
            {
                printf( "Can not get surface! SDL_Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Main loop flag
                bool quit = false;
                //Event handler
                SDL_Event e;

                // array of pixels we will manipulate
                uint32_t* pixels = ((Uint32 *) (gScreenSurface->pixels));


                int framecount = 0;
                uint64_t NOW = SDL_GetPerformanceCounter();
                uint64_t LAST = 0;

                unsigned int timer = 0;
                // Main Loop
                while( !quit )
                {
                    // Handle user input
                    if( SDL_PollEvent( &e ) != 0 && (SDL_QUIT == e.type || (SDL_KEYDOWN == e.type && SDLK_q == e.key.keysym.sym) ))
                    {
                        quit = true;
                    }

                    // FPS counter
                    if (framecount++ > 100)
                    {
                        LAST = NOW;
                        NOW = SDL_GetPerformanceCounter();
                        printf( "FPS: %f\n" , 100000.0/(double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() ));
                        framecount = 0;
                    }

                    // Fill Surface
                    for (unsigned int y = 0; y < gScreenSurface->h; y++)
                    {
                        unsigned int index0 = y * gScreenSurface->w;
                        for (unsigned int x = 0; x < gScreenSurface->w; x++)
                        {
                            uint32_t newPixel = 0xFF000000;            // Gamma
                            newPixel |= ((x-timer)&0xFF) << 16 ;       // R
                            newPixel |= ((y+timer)&0xFF) << 8 ;        // G
                            newPixel |= (timer & 0xFF);                // B
                            pixels[index0+x] = newPixel;
                        }
                    }
		    timer++;
                    //Update the surface
                    SDL_UpdateWindowSurface( gWindow );
                }

                SDL_FreeSurface( gScreenSurface );
                gScreenSurface = NULL;
            }
            SDL_DestroyWindow( gWindow );
            gWindow = NULL;
        }
        SDL_Quit();
    }
    return 0;
}
