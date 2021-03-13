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
    ~App();

    void Init();
	void Run();

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
