#pragma once

enum EventType
{
    TRANSACTION = 0,
};

class AEvent
{
public:
    AEvent(EventType type) { _type = type; }
    virtual std::string ToString() { return "Generic AEvent"; }
    EventType Type() { return _type; }

public:
    EventType _type;
};