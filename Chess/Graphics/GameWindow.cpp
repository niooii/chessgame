#include "GameWindow.h"

GameWindow::GameWindow(const char* title, int w, int h)
{
	SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
	SDL_SetWindowTitle(window, title);
	Textures::Generate(renderer);

	game = Game{};
	game.InitGame();
	//sets boardrenderer board target.
	br.Init(game.GetBoard());

	std::shared_ptr<Agent> agent1 = std::make_shared<RandomAgent>(WHITE);
	std::shared_ptr<Agent> agent2 = std::make_shared<RandomAgent>(BLACK);

	game.SetAgents(agent1, agent2);
	gametimer.Reset();
}

void GameWindow::Update()
{
	if (autoplay)
	{
		if (game.State() != IN_PROGRESS)
		{
			std::cout << game.State() << " in " << gametimer.ElapsedSeconds() << " seconds." << '\n';
			game.Reset();
			gametimer.Reset();
			return;
		}
		if (Agent1Turn)
		{
			game.Agent1Move();
		}
		else
		{
			game.Agent2Move();
		}
		Agent1Turn = !Agent1Turn;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//drawing goes here

	//Debug dangertile drawing...
	/*Positions& p = game.GetPositionObject();
	wt = p.TilesAttackedByTeam(WHITE);
	bt = p.TilesAttackedByTeam(BLACK);
	for (Tile* t : wt)
	{
		br.SetColor(t, { 0,255,0,255 });
	}
	for (Tile* t : bt)
	{
		if (wt.find(t) != wt.end())
		{
			br.SetColor(t, { 255,0,255,255 });
		}
		else
		{
			br.SetColor(t, { 0,0,255,255 });
		}
	}*/

	br.Draw(renderer);

	SDL_RenderPresent(renderer);

	/*for (Tile* t : wt)
	{
		br.RevertColor(t);
	}
	for (Tile* t : bt)
	{
		br.RevertColor(t);
	}

	wt.clear();
	bt.clear();*/
}

void GameWindow::HandleInput()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;


		case SDL_KEYDOWN:

			switch (event.key.keysym.sym)
			{

			case SDLK_ESCAPE:
				exit(0);
				break;

			case SDLK_r:
				std::cout << "RESETING" << '\n';
				game.Reset();
				break;

			case SDLK_u:
				game.UndoLastMove();
				break;
				 
			case SDLK_i:
				game.RedoLastMove();
				break;

			case SDLK_y:
				autoplay = !autoplay;
				break;

			case SDLK_t:
				
				if (Agent1Turn)
				{
					game.Agent1Move();
				}
				else
				{
					game.Agent2Move();
				}
				Agent1Turn = !Agent1Turn;

				break;

			}
			break;


		case SDL_WINDOWEVENT:

			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				int w = event.window.data1;
				int h = event.window.data2;
				std::cout << "resized viewport to width: " << w << ", " << h << "\n";

				break;
			}

			break;


		case SDL_MOUSEBUTTONDOWN:
			//Dont worry about the logic, just trust it.
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				Tile* clickedtile = br.TileAtClick(event.button.x, event.button.y);

				if (clickedtile != nullptr)
				{
					Board* board = game.GetBoard();

					//Check if there is an active piece, if there is, check if move can be performed.
					Piece* UserActivePiece = game.GetActivePiece();
					if (UserActivePiece != nullptr)
					{
						std::vector<Tile*>& UserAvailableMoves = game.GetUserAvailableMoves();
						//If tile is valid, do move.
						if (std::find(UserAvailableMoves.begin(), UserAvailableMoves.end(), clickedtile) != UserAvailableMoves.end())
						{
							bool promo{ false };
							//check if move shoudl be promotion move
							if (UserActivePiece->Type() == PAWN && (clickedtile->row == 1 || clickedtile->row == board->Rows()))
								promo = true;
							Move m{ UserActivePiece , clickedtile, promo, QUEEN };
							game.DoMove(m);
							//Reset colors
							for (Tile*& t : UserAvailableMoves)
							{
								br.RevertColor(t);
							}
							game.UnsetActivePiece();
							return;
						}
						else
						{

							Piece* clickedpiece = board->PieceAtTile(clickedtile);
							if (clickedpiece == nullptr)
							{
								//Reset colors
								for (Tile*& t : UserAvailableMoves)
								{
									br.RevertColor(t);
								}
								game.UnsetActivePiece();
								return;
							}
							if (clickedpiece == UserActivePiece)
							{
								//Reset colors
								for (Tile*& t : UserAvailableMoves)
								{
									br.RevertColor(t);
								}
								game.UnsetActivePiece();
								return;
							}
						}
						//Reset colors
						for (Tile*& t : UserAvailableMoves)
						{
							br.RevertColor(t);
						}
						game.UnsetActivePiece();
						//return;
					}

					Piece* clickedpiece = board->PieceAtTile(clickedtile);
					if (clickedpiece != nullptr)
					{
						std::cout << "Set active piece: " << clickedpiece->Type() << '\n';
						//If clickedpiece = the active piece
						if (game.GetActivePiece() == clickedpiece)
						{
							//Reset colors
							std::vector<Tile*>& UserAvailableMoves = game.GetUserAvailableMoves();
							for (Tile*& t : UserAvailableMoves)
							{
								br.RevertColor(t);
							}
							game.UnsetActivePiece();
						}
						//If there is no active piece set
						else if (game.GetActivePiece() == nullptr)
						{
							game.SetActivePiece(clickedpiece);
							std::cout << "this team has " << game.AllLegalMoves(clickedpiece->Team()).size() << " legal moves remaining." << '\n';
							//Set colors
							std::vector<Tile*>& UserAvailableMoves = game.GetUserAvailableMoves();
							for (Tile*& t : UserAvailableMoves)
							{
								br.SetColor(t, { 255,0,0,255 });
							}
						}
						//If there is another active piece
						else
						{
							//Reset colors
							std::vector<Tile*>& UserAvailableMoves = game.GetUserAvailableMoves();
							for (Tile*& t : UserAvailableMoves)
							{
								br.RevertColor(t);
							}
							game.UnsetActivePiece();
							//Update colors
							game.SetActivePiece(clickedpiece);
							//Set colors
							UserAvailableMoves = game.GetUserAvailableMoves();
							for (Tile*& t : UserAvailableMoves)
							{
								br.SetColor(t, { 255,0,0,255 });
							}
						}
					}
				}
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				Tile* clickedtile = br.TileAtClick(event.button.x, event.button.y);

				if (clickedtile != nullptr)
				{
					Piece* target = game.GetBoard()->PieceAtTile(clickedtile);
					if (target != nullptr)
					{
						game.KillPiece(target);
					}
				}
			}
			

			break;
		}
	}
}