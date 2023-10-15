#pragma once
#include <iostream>

enum TYPE
{
	KING,
	QUEEN,
	BISHOP,
	ROOK,
	KNIGHT,
	PAWN,
	NONE,
};

enum TEAM
{
	WHITE,
	BLACK,
};

enum STATE
{
	IN_PROGRESS,
	WHITE_CHECKMATE,
	BLACK_CHECKMATE,
	STALEMATE,
	FATAL,
};

std::ostream& operator<<(std::ostream& out, TYPE type);

std::ostream& operator<<(std::ostream& out, TEAM team);

std::ostream& operator<<(std::ostream& out, STATE state);