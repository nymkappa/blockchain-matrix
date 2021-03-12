#pragma once

#include <chrono>
#include "SDL.h"

class Symbol
{
public:
    Symbol();
    ~Symbol();

    Symbol(Symbol &&);
    Symbol &operator=(Symbol &&other);

    void Update(double deltaTime);
    void Draw(SDL_Renderer* sldRenderer, SDL_Texture *texture);

public:
    float _y;

private:
    float _speed;
    int _x;
    int _size;
};