#pragma once

#include <iostream>
#include <vector>

#include "EventQueue.hpp"

/**
 * Connect and listen to a websocket to receive new Bitcoin transaction in real time
 * Store transaction info in a message queue
 */
class Backend
{
public:
    Backend();

    void Run();
    void Exit();

    void SetEventQueue(std::shared_ptr<EventQueue> events) { _events = events; }

private:
    std::vector<std::string> Split(std::string&& s, std::string delimiter);

public:
    bool _exitFlag;
    std::shared_ptr<EventQueue> _events;
};