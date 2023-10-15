#include "Piece.h"

Piece::Piece(TYPE type, TEAM team, Tile* startingtile)
	: currenttile(startingtile), originaltile(startingtile), piecetype(type), startingtype(type), pieceteam(team)
{
	switch (type)
	{
	case PAWN:
		points = 1;
		break;
		
	case KNIGHT:
		points = 3;
		break;

	case BISHOP:
		points = 3;
		break;

	case ROOK:
		points = 5;
		break;

	case QUEEN:
		points = 9;
		break;

	case KING:
		points = 999;
		break;
	}
}

TYPE Piece::Type()
{
	return piecetype;
}

TYPE Piece::StartingType()
{
	return startingtype;
}

void Piece::SetType(TYPE newtype)
{
	piecetype = newtype;
	switch (newtype)
	{
	case PAWN:
		points = 1;
		break;

	case KNIGHT:
		points = 3;
		break;

	case BISHOP:
		points = 3;
		break;

	case ROOK:
		points = 5;
		break;

	case QUEEN:
		points = 9;
		break;

	case KING:
		points = 999;
		break;
	}
}

TEAM Piece::Team()
{
	return pieceteam;
}

Tile* Piece::CurrentTile()
{
	return currenttile;
}

Tile* Piece::StartingTile()
{
	return originaltile;
}

void Piece::SetTile(Tile* newtile)
{
	currenttile = newtile;
}

int Piece::Kill()
{
	alive = false;
	return points;
}

void Piece::Unkill()
{
	alive = true;
}

bool Piece::IsDead()
{
	return !alive;
}

bool operator==(Move& m, Move& m_)
{
	return (m.newtype == m_.newtype && m.from == m_.from && m.to == m_.to && m.moved == m_.moved);
}