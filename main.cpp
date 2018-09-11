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


                unsigned int framecount = 0;
                uint64_t NOW = SDL_GetPerformanceCounter();
                uint64_t LAST = 0;

		unsigned int width = gScreenSurface->w;
		unsigned int height = gScreenSurface->h;
		unsigned int beginNextRow = width;
		unsigned int fieldCount = width*height;

                // Main Loop
                while( !quit )
                {
                    // FPS counter
	            framecount++;
		    // Handle user input
                    if( SDL_PollEvent( &e ) != 0)
		    {
                        if ((SDL_QUIT == e.type || (SDL_KEYDOWN == e.type && SDLK_q == e.key.keysym.sym) ))
			{
                            quit = true;
			}

			if (SDL_KEYDOWN == e.type)
			{
                        // FPS output
                            LAST = NOW;
                            NOW = SDL_GetPerformanceCounter();
                            printf( "FPS: %f\n", framecount/(double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency() ));
                            framecount = 0;
			}
                    }


                    // Fill Surface
                    for (unsigned int offset = 0; offset < fieldCount; offset=beginNextRow)
                    {
			beginNextRow = offset+width;
                        for (unsigned int i = offset; i < beginNextRow; i++)
                        {
                            pixels[i] = (0xFF000000 | ((framecount & 0xFF) << 16) /*R*/ | ((framecount & 0xFF) << 8) /*G*/ | (framecount & 0xFF) /*B*/); 
			}
                    }
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
