#include <string>
#include <exception>
#include "App.hpp"
#include "SDLException.hpp"

App::App()
{
    std::cout << "App constructor\n";

    _window = nullptr;
    _exitFlag = false;
}

void App::Init()
{
    InitSDL();
    InitBackend();
    InitEventQueue();
}

void App::Exit()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void App::Run()
{
    SDL_Event e;

    while (!_exitFlag)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                _exitFlag = true;
            }
        }

        ProcessBackendEvents();
    }

    // Terminate backend thread
    _backend->Exit();
    _backendThread.join();
}

/**
 * Initialize SDL library and create a window
 */
void App::InitSDL()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw SDLException("SDL could not initialize! SDL_Error:" + std::string(SDL_GetError()));
    }

    // Create the window - Ressource is managed by SDL
    _window = SDL_CreateWindow(
        "BlockchainMatrix",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_SHOWN);

    if (_window == NULL)
    {
        throw SDLException("Window could not be created! SDL_Error:" + std::string(SDL_GetError()));
    }
}

/**
 * Start listening to the blockchain.com websocket in a new thread and save new incoming
 * Bitcoin transaction into a message queue read by the main thread
 */
void App::InitBackend()
{
    _backend = std::make_shared<Backend>();
    _backend->Init();

    _backendThread = std::thread(&Backend::Run, _backend);
}

/**
 * Create the event queue and share a reference on it
 */
void App::InitEventQueue()
{
    if (_backend == nullptr)
    {
        throw std::exception("Backend has not been initialized");
    }

    _events = std::make_shared<EventQueue>();
    _backend->SetEventQueue(_events);
}

/**
 * Process currently pending backend events
 */
void App::ProcessBackendEvents()
{
    if (_events == nullptr)
    {
        throw std::exception("Events queue has not been initialized");
    }

    while (_events->dataIsAvailable())
    {
        std::unique_ptr<AEvent> ev(_events->get());

        std::cout << "Main thread is processing " << ev->ToString() << "\n";
    }
}