#pragma once

#include <iostream>
#include <thread>
#include <memory>
#include "SDL.h"
#include "Backend.hpp"
#include "EventQueue.hpp"
#include "Renderer.hpp"

#undef main // We don't need SDL default main function

class App {
public:
    App();
    ~App() { std::cout << "App destructor\n"; }

    void Init();
	void Run();
    void Exit();

private:
    void InitBackend();
    void InitEventQueue();
    void ProcessBackendEvents(Renderer &renderer);

private:
    bool _exitFlag;

    std::thread _backendThread;
    std::shared_ptr<Backend> _backend;

    std::shared_ptr<EventQueue> _events;
};
