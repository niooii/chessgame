#pragma once
#include "Headers/Enums.h"
#include "Board.h"
#include <unordered_set>

class pos
{
public:
	bool map[8][8]{ 0 };

	pos(Board* target, TYPE type, TEAM team);
	TYPE PieceType();
	TEAM PieceTeam();

	void AddPiece(Piece* p);
	void RemovePiece(Piece* p);
	
	//Returns all tiles being attacked by the piecetype for a specific team.
	std::unordered_set<Tile*>& GetAttackedTiles();
	//Updates the tiles being attacked by the pieces (has alive checks).
	void Update();

	bool& PositionMap();

	//locks in the original pieces for the pos object.
	void LockIn();

	//sets pieces vector to original pieces.
	void Reset();

private:
	Board* board;

	std::unordered_set<Piece*> pieces;
	std::unordered_set<Tile*> attackedTiles;

	TYPE piecetype;
	TEAM pieceteam;

	std::unordered_set<Piece*> originalPieces;

	
};