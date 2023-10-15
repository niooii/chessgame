#pragma once

#include "BoardRenderer.h"
#include "../Game.h"
#include <algorithm>
#include "../../Agents/Agent.h"
#include "../../Agents/RandomAgent.h"
#include "../../Utils/Timer.h"

//Main window for displaying the game. Also for handling inputs.
class GameWindow
{
public:
	GameWindow(const char* title, int w, int h);

	//Draws new frames.
	void Update();

	//Handle input to window.
	void HandleInput();
	
private:
	Game game;

	//Graphics stuff

	BoardRenderer br;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	//for debugging purposes
	std::unordered_set<Tile*> wt;
	std::unordered_set<Tile*> bt;

	bool autoplay{ false };
	bool Agent1Turn{true};

	Timer gametimer{};
};