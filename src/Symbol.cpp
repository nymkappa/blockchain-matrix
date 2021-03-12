#include <iostream>
#include "Symbol.hpp"
#include "SDLException.hpp"

Symbol::Symbol()
{
    _x = rand() % 800;
    _y = (float)(-rand() % 2000);
    _size = 10 + rand() % 10;
    _speed = 0.5f + (rand() % 100) / 100.0f;
}

Symbol::~Symbol()
{
}

Symbol::Symbol(Symbol &&s)
{
    _x = s._x;
    _y = s._y;
    _size = s._size;
    _speed = s._speed;
}

Symbol& Symbol::operator=(Symbol&& s)
{
    _x = s._x;
    _y = s._y;
    _size = s._size;
    _speed = s._speed;

    return *this;
}

void Symbol::Update(double deltaTime)
{
    _y += (float)(100.0 * deltaTime) * _speed;
}

void Symbol::Draw(SDL_Renderer *sldRenderer, SDL_Texture *texture)
{
    SDL_Rect fillRect = {_x, (int)_y, _size, _size};
    SDL_RenderCopy(sldRenderer, texture, NULL, &fillRect);
}