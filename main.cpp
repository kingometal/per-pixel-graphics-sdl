#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int MAX_FPS = 30;

void run()
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
                uint64_t currentFrameOutputTime = SDL_GetPerformanceCounter();
                uint64_t lastFrameOutputTime = currentFrameOutputTime;
                uint64_t LAST = 0;
		double min_frame_time = 1.0/(double)MAX_FPS;

		unsigned int width = gScreenSurface->w;
		unsigned int height = gScreenSurface->h;
		unsigned int beginNextRow = width;
		unsigned int fieldCount = width*height;

                // Main Loop
                while( !quit )
                {
                    // FPS counter
//	            framecount++;
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
                            pixels[i] = (0xFF000000 | ((offset & 0xFF) << 16) /*R*/ | ((framecount & 0xFF) << 8) /*G*/ | ((i+framecount) & 0xFF) /*B*/); 
			}
                    }
                    //Update the surface, but not more often than the maximum frames per seconds (FPS)
                    currentFrameOutputTime = SDL_GetPerformanceCounter();
		    if ((double)(currentFrameOutputTime-lastFrameOutputTime)/(double) SDL_GetPerformanceFrequency() > min_frame_time)
		    {
                        SDL_UpdateWindowSurface( gWindow );
//                        printf( "update duration: %f ms\n", (double) (SDL_GetPerformanceCounter() - currentFrameOutputTime)*1000.0 / (double)SDL_GetPerformanceFrequency() );
                        lastFrameOutputTime = currentFrameOutputTime;
	                framecount++;
		    }
                }

                SDL_FreeSurface( gScreenSurface );
                gScreenSurface = NULL;
            }
            SDL_DestroyWindow( gWindow );
            gWindow = NULL;
        }
        SDL_Quit();
    }
}

int main(int argc, char** argv) 
{
    run();
    return 0;
}
