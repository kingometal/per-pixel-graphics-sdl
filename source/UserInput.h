#ifndef USERINPUT_H
#define USERINPUT_H
#include "Interfaces/IUserInput.h"

class UserInput: public IUserInput
{
public:
    UserInput();
    bool IsQuitRequested();
    char CheckKeyPress();
private:
    bool QuitRequested;
    char LastKeyPressed;
};

#endif // USERINPUT_H
