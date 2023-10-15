#pragma once

#include <arrayfire.h>
#include "pos.h"
#include "Headers/Enums.h"

class Positions
{
public:
	Positions();

	//Inits with target.
	void Init(Board* target);

	void Update(TYPE piecetype, TEAM pieceteam);
	void UpdateAll();

	//Get set of Tiles attacked by the specified team.
	std::unordered_set<Tile*> TilesAttackedByTeam(TEAM team);

	//Switches piece to another pos object. has to be called before original piece is changed.
	void SwitchPiece(Piece* p, TYPE newtype);

	//Returns all TYPEs attacking a specific Tile, for the specified team. Returns only beam types (queen, rook, bishop).
	std::unordered_set<TYPE> TypesAttackingTile(Tile* t, TEAM attacking);

	//what do you think it does, genius
	void ResetAll();

	//Returns a 8x8x12 tensor of all the pieces positions in a specified order.
	af::array GetAsTensor();

private:
	std::vector<pos> posvec;
};