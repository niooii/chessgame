#include <iostream>
#include <SDL.h>
#undef main
#include <arrayfire.h>
#include "Chess/Board.h"
#include "Utils/Timer.h"
#include "Chess/Graphics/GameWindow.h"
#include "Chess/Graphics/TextureManager.h"

int main()
{
	Timer t{};

	SDL_Init(SDL_INIT_EVERYTHING);

	//SDL_Window* w = SDL_CreateWindow("yes", 200, 200, 800, 800, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	af::setBackend(AF_BACKEND_CUDA);
	//Board b{};

	//b.InitPieces();

	//int testrow = 8;
	//int testcol = 8;
	//std::cout << b.PieceAtPos(testrow, testcol)->Type() << '\n';
	//std::cout << b.PieceAtPos(testrow, testcol)->Team() << '\n';

	GameWindow gw{"TITLE", 800, 800};

	while (true)
	{
		gw.HandleInput();
		gw.Update();
	}

	std::cout << "Execution finished in " << t.ElapsedSeconds() << " seconds." << '\n';
}