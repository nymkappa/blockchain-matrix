#include <random>
#include <iostream>
#include <thread>
#include "Renderer.hpp"
#include "SDLException.hpp"
#include "SDL_image.h"

using namespace std::chrono_literals;

Renderer::Renderer()
{
    _start = std::chrono::system_clock::now();

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

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        throw SDLException("SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()));
    }

    LoadTexture("btc.png");
}

Renderer::~Renderer()
{
    //Free loaded image
    SDL_DestroyTexture(_sdlTexture);
    _sdlTexture = NULL;

    SDL_DestroyRenderer(_sdlRenderer);
    SDL_DestroyWindow(_sdlWindow);

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture *Renderer::LoadTexture(std::string path)
{
    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        throw SDLException("Unable to load image! SDL_image Error: " + std::string(IMG_GetError()));
    }
    else
    {
        //Create texture from surface pixels
        _sdlTexture = SDL_CreateTextureFromSurface(_sdlRenderer, loadedSurface);
        if (_sdlTexture == NULL)
        {
            throw SDLException("Unable to create texture! SDL Error: " + std::string(SDL_GetError()));
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return _sdlTexture;
}

void Renderer::AddSymbol()
{
    if (_symbols.size() > 6000)
    {
        return; // Ignore it, already too many things to render
    }

    Symbol symbol;
    _symbols.push_back(std::move(symbol));
}

void Renderer::Render()
{
    const int OFF_SCREEN_Y = 900;
    static float framePerSeconds = 30.0;

    // Clear screen
    SDL_SetRenderDrawColor(_sdlRenderer, 0, 0, 0, 0);
    SDL_RenderClear(_sdlRenderer);

    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - _start;
    double deltaTime = elapsed_seconds.count();

    if (deltaTime < 1.0 / framePerSeconds)
    {
        // Skip this frame
        std::this_thread::sleep_for(1ms);
        return;
    }

    //std::cout << "Render. Vector size " << _symbols.size() << "\n";

    _start = std::chrono::system_clock::now();

    for (auto it = _symbols.begin(); it != _symbols.end();)
    {
        Symbol &s(*it);

        s.Update(deltaTime);
        s.Draw(_sdlRenderer, _sdlTexture);

        // When a symbol is out of the screen, we don't need it anymore
        if (s.GetY() > OFF_SCREEN_Y)
        {
            it = _symbols.erase(it);
        }
        else
        {
            ++it;
        }
    }

    SDL_RenderPresent(_sdlRenderer);
}