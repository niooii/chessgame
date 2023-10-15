#pragma once

#include "../Chess/Piece.h"
#include <vector>
#include <map>

class Board
{
public:
	//An object containing an array of Tile objects, and a set of Piece objects.
	Board();

	//Returns number of rows, starting from 1 (not index based).
	int Rows();
	//Returns number of rows, starting from 1 (not index based).
	int Cols();

	//Returns the 2D Tile vector.
	std::vector<std::vector<Tile>>& Tiles();

	//Returns the tile vector for White captured pieces.
	std::vector<Tile>& WhiteCaptured();

	//Returns the tile vector for Black captured pieces.
	std::vector<Tile>& BlackCaptured();

	//Returns the Piece vector.
	std::vector<Piece>& Pieces();

	/*Returns a pointer to the Tile at the specified position(not index based).
	If it doesn't exist, returns nullptr.*/
	Tile* TileAtPos(int row, int col);

	/*Returns a pointer to the Piece at the specified position(not index based).
	If it doesn't exist, returns nullptr.*/
	Piece* PieceAtPos(int row, int col);

	/*Returns a pointer to the Piece at the specified Tile.
	If it doesn't exist, returns nullptr.*/
	Piece* PieceAtTile(Tile* t);

	//Initializes pieces (i hardcoded).
	void InitPieces();

	//Changes piece to specified type.
	void ChangePiece(Piece* target, TYPE newtype);

	//Helper stuff.
	Tile* TileTopLeft(Tile* t);
	Tile* TileTopRight(Tile* t);
	Tile* TileBottomLeft(Tile* t);
	Tile* TileBottomRight(Tile* t);

	Tile* TileTop(Tile* t);
	Tile* TileBottom(Tile* t);
	Tile* TileLeft(Tile* t);
	Tile* TileRight(Tile* t);

	//Returns the next free WhiteCapturedTile and increments.
	Tile* NextWhiteCapturedTile();

	//Returns the next free BlackCapturedTile and increments.
	Tile* NextBlackCapturedTile();

	//Returns a garbage tile meant for temp storing a piece.
	Tile* GarbageTile();

	//Resets all positions and unkills pieces.
	void Reset();
	
	//dumb variables get to be public.
	int bct_index{ 0 };
	int wct_index{ 0 };

private:
	std::vector<std::vector<Tile>> tiles;
	std::vector<Tile> whiteCaptured;
	std::vector<Tile> blackCaptured;
	std::vector<Piece> pieces;
	Tile garbageTile;
	int rows, cols;
};