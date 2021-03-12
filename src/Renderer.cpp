#include <random>
#include <iostream>
#include "Renderer.hpp"
#include "SDLException.hpp"

Renderer::Renderer()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw SDLException("SDL could not initialize! SDL_Error:" + std::string(SDL_GetError()));
    }

    // Create the window - Ressource is managed by SDL
    _sdlWindow = SDL_CreateWindow(
        "BlockchainMatrix",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_SHOWN);

    if (_sdlWindow == NULL)
    {
        throw SDLException("Window could not be created! SDL_Error:" + std::string(SDL_GetError()));
    }

    _sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_sdlRenderer == NULL)
    {
        throw SDLException("Renderer could not be created! SDL_Error:" + std::string(SDL_GetError()));
    }

    SDL_SetRenderDrawColor(_sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(_sdlRenderer);
    SDL_DestroyWindow(_sdlWindow);
}

void Renderer::AddSymbol()
{
    _symbols.push_back(std::move(Symbol(rand() % 800, rand() % 600, rand() % 10 + 5, '0')));
}

void Renderer::Render()
{
    // Clear screen
    SDL_SetRenderDrawColor(_sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_sdlRenderer);

    for (int i = 0; i < _symbols.size(); ++i)
    {
        const Symbol &s(_symbols[i]);

        SDL_Rect fillRect = {s._x, s._y, s._size, s._size};
        SDL_SetRenderDrawColor(_sdlRenderer, s._red, s._green, s._blue, 255);
        SDL_RenderFillRect(_sdlRenderer, &fillRect);
    }

    SDL_RenderPresent(_sdlRenderer);
}