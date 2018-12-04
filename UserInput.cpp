#include "UserInput.h"
#include <SDL2/SDL.h>

namespace
{
    void ProcessEvents(bool & QuitRequested)
    {
        SDL_Event e;
        // Handle user input
        while( SDL_PollEvent( &e ) != 0)
        {
            if ((SDL_QUIT == e.type || (SDL_KEYDOWN == e.type && SDLK_q == e.key.keysym.sym) ))
            {
                QuitRequested = true;
            }
        }
    }
}

UserInput::UserInput()
    : QuitRequested(false)
{

}

bool UserInput::IsQuitRequested()
{
    ProcessEvents(QuitRequested);
    return QuitRequested;
}
