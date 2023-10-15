#include <iostream>
#include <fstream>
#include "TextureManager.h"
#include <filesystem>


namespace Textures
{
    SDL_Texture* WhitePawn{ nullptr };
    SDL_Texture* BlackPawn{ nullptr };

    SDL_Texture* WhiteRook{ nullptr };
    SDL_Texture* BlackRook{ nullptr };

    SDL_Texture* WhiteKnight{ nullptr };
    SDL_Texture* BlackKnight{ nullptr };

    SDL_Texture* WhiteBishop{ nullptr };
    SDL_Texture* BlackBishop{ nullptr };

    SDL_Texture* WhiteQueen{ nullptr };
    SDL_Texture* BlackQueen{ nullptr };

    SDL_Texture* WhiteKing{ nullptr };
    SDL_Texture* BlackKing{ nullptr };

    void Generate(SDL_Renderer* Renderer)
    {
  /*      std::ifstream f("D:/VisualStudioProjects/LearningCPP/ihavecancer/Chess/Graphics/Textures/whitepawn.png");
        if (!f)
        {
            std::cout << "could not find texture paths" << '\n';
            return;
        }*/
        //I WILL FIX THIS LATER I SWEAR
        WhitePawn = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/whitepawn.png");
        BlackPawn = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/blackpawn.png");
        WhiteRook = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/whiterook.png");
        BlackRook = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/blackrook.png");
        WhiteKnight = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/whiteknight.png");
        BlackKnight = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/blackknight.png");
        WhiteBishop = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/whitebishop.png");
        BlackBishop = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/blackbishop.png");
        WhiteQueen = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/whitequeen.png");
        BlackQueen = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/blackqueen.png");
        WhiteKing = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/whiteking.png");
        BlackKing = IMG_LoadTexture(Renderer, "Chess/Graphics/Textures/blackking.png");
        std::cout << "loaded textures!" << '\n';
        std::cout << IMG_GetError() << '\n';
    }
}