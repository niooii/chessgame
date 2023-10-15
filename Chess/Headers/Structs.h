#pragma once

#include <iostream>

//Tile row and col are not index based (1-8 for example).
struct Tile
{
	Tile(int row, int col) : row(row), col(col) {};
	//Starts at 1.
	int row;
	//Starts at 1.
	int col;
};

std::ostream& operator<<(std::ostream& out, Tile t);