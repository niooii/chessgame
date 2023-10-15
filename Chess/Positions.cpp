#include "Positions.h"

Positions::Positions()
{

}

void Positions::Init(Board* target)
{
	std::vector<Piece>& pieces = target->Pieces();

	for (Piece& p : pieces)
	{
		bool found{ false };
		for (pos& pos : posvec)
		{
			if (pos.PieceTeam() == p.Team() && pos.PieceType() == p.Type())
			{
				found = true;
				pos.AddPiece(&p);
			}
		}

		if (!found)
		{
			posvec.emplace_back(target, p.Type(), p.Team());
			posvec.at(posvec.size() - 1).AddPiece(&p);
		}
	}

	for (pos& pos : posvec)
	{
		pos.LockIn();
		pos.Update();
	}
}

void Positions::Update(TYPE piecetype, TEAM pieceteam)
{
	for (pos& p : posvec)
	{
		if (p.PieceType() == piecetype && p.PieceTeam() == pieceteam)
		{
			p.Update();
			break;
		}
	}
}

void Positions::UpdateAll()
{
	for (pos& p : posvec)
	{
		p.Update();
	}
}

std::unordered_set<Tile*> Positions::TilesAttackedByTeam(TEAM team)
{
	std::unordered_set<Tile*> t;
	for (pos& p : posvec)
	{
		if (p.PieceTeam() == team)
		{
			std::unordered_set<Tile*> temp = p.GetAttackedTiles();
			t.insert(temp.begin(), temp.end());
		}
	}
	return t;
}

void Positions::SwitchPiece(Piece* p, TYPE newtype)
{
	//find piece and remove it
	for (pos& pos : posvec)
	{
		if (pos.PieceType() == p->Type() && pos.PieceTeam() == p->Team())
		{
			pos.RemovePiece(p);
			break;
		}
	}
	//now add the piece to the correct pos object.
	for (pos& pos : posvec)
	{
		if (pos.PieceType() == newtype && pos.PieceTeam() == p->Team())
		{
			pos.AddPiece(p);
			break;
		}
	}
}

std::unordered_set<TYPE> Positions::TypesAttackingTile(Tile* t, TEAM attacking)
{
	std::unordered_set<TYPE> types;

	for (pos& p : posvec)
	{
		if (p.PieceType() == PAWN || p.PieceType() == KNIGHT || p.PieceType() == KING)
			continue;
		std::unordered_set<Tile*> tiles = p.GetAttackedTiles();
		if (tiles.find(t) != tiles.end())
		{
			types.insert(p.PieceType());
		}
	}
	return types;
}

void Positions::ResetAll()
{
	for (pos& p : posvec)
	{
		p.Reset();
	}
}

af::array Positions::GetAsTensor()
{
	af::array tensor(8, 8, 12, f32); // Initialize an empty 12x8x8 tensor
	int i{};
	for (int i = 0; i < 12; i++)
	{
		for (int row = 0; row < 8; row++)
		{
			for (int col = 0; col < 8; col++)
			{
				// Assign the value from posvec to the corresponding location in the tensor
				tensor(row, col, i) = posvec[i].map[row][col] ? 1.0f : 0.0f;
			}
		}
	}
	return tensor;
}