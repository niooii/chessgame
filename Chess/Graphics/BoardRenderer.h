#pragma once

#include <SDL.h>
#include "../Board.h"
#include "TextureManager.h"

//A tile meant for rendering to the screen, origin of dest rectangle is in the center when initialized with screen coords.
struct GraphicTile
{
	GraphicTile(Tile* corresponding, int screenx, int screeny, int w, int h, SDL_Color color)
		: color(color), correspondingTile(corresponding)
	{
		dest = SDL_Rect{screenx - w/2, screeny - h/2, w, h};
	};

	SDL_Rect dest;
	SDL_Color color;
	bool usetempcolor{ false };
	SDL_Color tempcolor{};

	Tile* correspondingTile;
};

//Essentially just a texture of a piece with a dest rectangle.
struct GraphicPiece
{
	GraphicPiece(Piece* corresponding, SDL_Texture* texture)
	: correspondingPiece(corresponding), texture(texture) 
	{
		int w, h;
		SDL_QueryTexture(texture, 0, 0, &w, &h);
		dest = SDL_Rect{ 0,0,w,h };
		smallDest = SDL_Rect{ 0,0,w/2,h/2 };
		prevType = corresponding->Type();
	};

	Piece* correspondingPiece;
	TYPE prevType;
	SDL_Texture* texture;
	SDL_Rect smallDest;
	SDL_Rect dest;
};

//This class contains all the board rendering logic and stuff. 
class BoardRenderer
{
public:
	BoardRenderer();

	//Sets target board for rendering
	void Init(Board* target);
	//Self explanatory. Draws tiles at centered coordinates.
	void Draw(SDL_Renderer* renderer);

	//Returns a tile at the specified screen coordinates. If it cannot be found, returns nullptr.
	Tile* TileAtClick(int x, int y);

	GraphicTile* GraphicTileForTile(Tile* t);
	GraphicPiece* GraphicPieceForPiece(Piece* p);

	void SetColor(Tile* t, SDL_Color tempcolor);
	void RevertColor(Tile* t);

private:
	Board* target;

	std::vector<GraphicTile> rendertiles;
	std::vector<GraphicTile> killedtiles;
	std::vector<GraphicPiece> renderpieces;
};