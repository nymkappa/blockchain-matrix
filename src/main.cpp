#include <iostream>

#include "App.hpp"
#include "SDLException.hpp"

int main()
{
    // Initialize SDL app
    App app;

    try
    {
        app.Init();
        app.Run();
    }
    catch (const SDLException &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}