#pragma once

#include <iostream>
#include <thread>
#include <memory>
#include "SDL.h"
#include "Backend.hpp"
#include "EventQueue.hpp"

#undef main // We don't need SDL default main function

class App {
public:
    App();
    ~App() { std::cout << "App destructor\n"; }

    void Init();
	void Run();
    void Exit();

private:
    void InitSDL();
    void InitBackend();
    void InitEventQueue();
    void ProcessBackendEvents();

private:
    bool _exitFlag;
    SDL_Window *_window; // Ressource is managed by SDL

    std::thread _backendThread;
    std::shared_ptr<Backend> _backend;

    std::shared_ptr<EventQueue> _events;
};
