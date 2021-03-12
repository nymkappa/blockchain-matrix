#include <string>
#include <exception>
#include "App.hpp"
#include "Renderer.hpp"

App::App()
{
    std::cout << "App constructor\n";
    _exitFlag = false;
}

void App::Init()
{
    InitBackend();
    InitEventQueue();
}

void App::Exit()
{
    SDL_Quit();
}

void App::Run()
{
    SDL_Event e;
    Renderer renderer;

    while (!_exitFlag)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                _exitFlag = true;
            }
        }

        ProcessBackendEvents(renderer);

        renderer.Render();
    }

    // Terminate backend thread
    _backend->Exit();
    _backendThread.join();
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
void App::ProcessBackendEvents(Renderer &renderer)
{
    if (_events == nullptr)
    {
        throw std::exception("Events queue has not been initialized");
    }

    while (_events->dataIsAvailable())
    {
        std::unique_ptr<AEvent> ev(_events->get());

        std::cout << "Main thread is processing " << ev->ToString() << "\n";
        renderer.AddSymbol();
    }
}