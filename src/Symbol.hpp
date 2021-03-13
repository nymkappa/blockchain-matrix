#pragma once

#include <chrono>
#include "SDL.h"

class Symbol
{
public:
    Symbol();
    Symbol(const Symbol &);
    Symbol(Symbol &&);
    Symbol &operator=(const Symbol &);
    Symbol &operator=(Symbol &&);

    void Update(double deltaTime);
    void Draw(SDL_Renderer *sldRenderer, SDL_Texture *texture);

    float GetY() { return _y; }

private:
    float _speed;
    int _x;
    float _y;
    int _size;
};