#pragma once

#include <deque>
#include <mutex>
#include <iostream>
#include "AEvent.hpp"

class EventQueue
{
public:
    bool dataIsAvailable()
    {
        std::lock_guard<std::mutex> myLock(_mutex);
        return !_events.empty();
    }

    std::unique_ptr<AEvent> get()
    {
        // perform deque modification under the lock
        std::lock_guard<std::mutex> uLock(_mutex);

        // remove first deque element from queue
        std::unique_ptr<AEvent> ev = std::move(_events.front());
        _events.pop_front();

        return ev; // will not be copied due to return value optimization (RVO) in C++
    }

    void push(std::unique_ptr<AEvent> ev)
    {
        // perform deque modification under the lock
        std::lock_guard<std::mutex> uLock(_mutex);

        // add deque to queue
        // std::cout << "  AEvent '" << ev->ToString() << "' is added to the queue" << std::endl;
        _events.emplace_back(std::move(ev));
    }

private:
    std::deque<std::unique_ptr<AEvent>> _events;
    std::mutex _mutex;
};
