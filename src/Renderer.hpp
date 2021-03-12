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

    SDL_Texture* LoadTexture(std::string path);
    void AddSymbol();

private:
    std::vector<Symbol> _symbols;

    // Ressource managed by SDL
    SDL_Window *_sdlWindow;
    SDL_Renderer *_sdlRenderer;
    SDL_Texture *_sdlTexture;

    std::chrono::time_point<std::chrono::system_clock> _start;
};