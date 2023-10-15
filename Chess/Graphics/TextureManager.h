#pragma once

#include <SDL.h>
#include <SDL_image.h>

namespace Textures
{
    extern SDL_Texture* WhitePawn;
    extern SDL_Texture* BlackPawn;

    extern SDL_Texture* WhiteRook;
    extern SDL_Texture* BlackRook;

    extern SDL_Texture* WhiteKnight;
    extern SDL_Texture* BlackKnight;

    extern SDL_Texture* WhiteBishop;
    extern SDL_Texture* BlackBishop;

    extern SDL_Texture* WhiteQueen;
    extern SDL_Texture* BlackQueen;

    extern SDL_Texture* WhiteKing;
    extern SDL_Texture* BlackKing;


    void Generate(SDL_Renderer* Renderer);
}