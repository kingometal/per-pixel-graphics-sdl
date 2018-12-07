#include "UserInput.h"
#include <SDL2/SDL.h>

namespace
{
    void ProcessEvents(bool & QuitRequested, char& LastKeyPressed)
    {

        SDL_Event e;
        // Handle user input
        while( SDL_PollEvent( &e ) != 0)
        {
            if ((SDL_QUIT == e.type || (SDL_KEYDOWN == e.type && SDLK_q == e.key.keysym.sym) ))
            {
                QuitRequested = true;
            }
            else if (SDL_KEYDOWN == e.type)
            {

                switch(e.key.keysym.sym)
                {
                    case SDLK_KP_PLUS:
                        LastKeyPressed = '+';
                    break;
                    case SDLK_KP_MINUS:
                        LastKeyPressed = '-';
                    break;
                }
            }
        }
    }
}

UserInput::UserInput()
    : QuitRequested(false)
    , LastKeyPressed(0)
{
}

bool UserInput::IsQuitRequested()
{
    ProcessEvents(QuitRequested, LastKeyPressed);
    return QuitRequested;
}

char UserInput::CheckKeyPress()
{
    char returnValue = LastKeyPressed;
    LastKeyPressed = 0;
    return returnValue;
}
