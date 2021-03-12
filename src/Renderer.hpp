#pragma once

#include <vector>
#include "Symbol.hpp"
#include "Renderer.hpp"
#include "SDL.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Init();
    void Render();
    void Exit();

    void AddSymbol();

private:
    std::vector<Symbol> _symbols;

    // Ressource managed by SDL
    SDL_Window *_sdlWindow;
    SDL_Renderer *_sdlRenderer;
};