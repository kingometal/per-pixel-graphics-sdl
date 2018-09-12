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
        SDL_Window* gWindow = SDL_CreateWindow( "Simple lightweight per-pixel drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
                uint64_t NOW = SDL_GetPerformanceCounter();
                uint64_t LAST = NOW;
                uint64_t currentFrameOutputTime = SDL_GetPerformanceCounter();
                uint64_t lastFrameOutputTime = currentFrameOutputTime;
		double min_frame_time = 1.0/(double)MAX_FPS;

		unsigned int width = SCREEN_WIDTH;
		unsigned int height = SCREEN_HEIGHT;

                // Main Loop
                while( !quit )
                {
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
                    for (unsigned int x = 0; x < width; x++)
                    {
                        for (unsigned int y = 0; y < height; y++)
                        {
			    SDL_SetRenderDrawColor(renderer, (framecount)%255, (y+framecount)%255, (x+framecount)%255, 255);
			    SDL_RenderDrawPoint(renderer, x, y);
			}
                    }
                    //Update the window, but not more often than the maximum frames per seconds (FPS)
                    currentFrameOutputTime = SDL_GetPerformanceCounter();
		    if ((double)(currentFrameOutputTime-lastFrameOutputTime)/(double) SDL_GetPerformanceFrequency() > min_frame_time)
		    {
                        SDL_RenderPresent(renderer);
//                        printf( "update duration: %f ms\n", (double) (SDL_GetPerformanceCounter() - currentFrameOutputTime)*1000.0 / (double)SDL_GetPerformanceFrequency() );
                        lastFrameOutputTime = currentFrameOutputTime;
	                framecount++;
		    }
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
    run();
    return 0;
}
