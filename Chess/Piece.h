#pragma once

#include "Headers/Enums.h"

#include "Headers/Structs.h"

class Piece
{
public:
	Piece(TYPE type, TEAM team, Tile* startingtile);

	TYPE Type();
	TYPE StartingType();
	void SetType(TYPE newtype);
	TEAM Team();

	Tile* CurrentTile();
	Tile* StartingTile();
	void SetTile(Tile* newtile);

	//Returns the points of the killed piece
	int Kill();
	//Unkills the piece specified (dont forget to set the tile appropriately)
	void Unkill();
	bool IsDead();

private:
	TYPE piecetype;
	TYPE startingtype;
	TEAM pieceteam;
	int points;
	bool alive{ true };

	Tile* currenttile;
	Tile* originaltile;
};

struct MoveLog
{
	MoveLog(Piece* moved, Piece* killed, Tile* from, Tile* to, bool ispromotion, TYPE originalType, TYPE newtype)
		: moved(moved), killed(killed), from(from), to(to), ispromotion(ispromotion), originalType(originalType), newType(newtype)
	{
	};

	Piece* moved;
	Piece* killed;

	Tile* from;
	Tile* to;

	bool ispromotion;

	TYPE originalType;
	TYPE newType;
};

struct Move
{
	Move(Piece* moved, Tile* to, bool ispromotion, TYPE newtype)
		: moved(moved), to(to), ispromotion(ispromotion), newtype(newtype)
	{
		if(moved != nullptr)
			from = moved->CurrentTile();
	};

	Piece* moved;

	Tile* from;
	Tile* to;

	bool ispromotion;

	TYPE newtype;
};

bool operator==(Move& m, Move& m_);


std::ostream& operator<<(std::ostream& out, STATE state);