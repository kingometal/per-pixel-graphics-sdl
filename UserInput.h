#ifndef USERINPUT_H
#define USERINPUT_H


class UserInput
{
public:
    UserInput();
    bool IsQuitRequested();
private:
    bool QuitRequested;
};

#endif // USERINPUT_H
