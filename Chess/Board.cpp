#include "Board.h"


Board::Board() : garbageTile(-2, -2)
{
	rows = 8;
	cols = 8;

	//initialize the 2d array first
	for (int i = 0; i < rows; i++)
	{
		tiles.emplace_back();
		for (int j = 0; j < cols; j++)
		{
			tiles[i].emplace_back(-1,-1);
		}
	}

	//set up the rows and cols with appropriate tiles
	for (int i = 0; i < rows; i++)
	{
		tiles.emplace_back();
		for (int j = 0; j < cols; j++)
		{
			tiles[i][j] = Tile(i + 1, j + 1);
		}
	}

	//set up the white and black captured rows

	for (int j = 0; j < cols * 2; j++)
	{
		whiteCaptured.emplace_back(-1, j);
	}

	for (int j = 0; j < cols * 2; j++)
	{
		blackCaptured.emplace_back(-1, j);
	}


}

Tile* Board::GarbageTile()
{
	return &garbageTile;
}

int Board::Rows()
{
	return rows;
}

int Board::Cols()
{
	return cols;
}


std::vector<std::vector<Tile>>& Board::Tiles()
{
	return tiles;
}

std::vector<Tile>& Board::WhiteCaptured()
{
	return whiteCaptured;
}


std::vector<Tile>& Board::BlackCaptured()
{
	return blackCaptured;
}

std::vector<Piece>& Board::Pieces()
{
	return pieces;
}


Tile* Board::TileAtPos(int row, int col)
{
	return ((row < 1 || row > rows || col < 1 || col > cols) ? nullptr : &tiles[row-1][col-1]);
}

Piece* Board::PieceAtPos(int row, int col)
{
	for (Piece& p : pieces)
	{
		if (p.CurrentTile()->row == row && p.CurrentTile()->col == col)
			return &p;
	}
	return nullptr;
}

Piece* Board::PieceAtTile(Tile* t)
{
	for (Piece& p : pieces)
	{
		if (p.CurrentTile()->row == t->row && p.CurrentTile()->col == t->col)
			return &p;
	}
	return nullptr;
}

#include <map>

// ...

void Board::InitPieces()
{
	// Initialize white pieces
	pieces.emplace_back(ROOK, WHITE, TileAtPos(8, 1));
	pieces.emplace_back(KNIGHT, WHITE, TileAtPos(8, 2));
	pieces.emplace_back(BISHOP, WHITE, TileAtPos(8, 3));
	pieces.emplace_back(QUEEN, WHITE, TileAtPos(8, 4));
	pieces.emplace_back(KING, WHITE, TileAtPos(8, 5));
	pieces.emplace_back(BISHOP, WHITE, TileAtPos(8, 6));
	pieces.emplace_back(KNIGHT, WHITE, TileAtPos(8, 7));
	pieces.emplace_back(ROOK, WHITE, TileAtPos(8, 8));

	for (int i = 1; i <= 8; i++)
	{
		pieces.emplace_back(PAWN, WHITE, TileAtPos(7, i));
	}

	// Initialize black pieces
	pieces.emplace_back(ROOK, BLACK, TileAtPos(1, 8));
	pieces.emplace_back(KNIGHT, BLACK, TileAtPos(1, 7));
	pieces.emplace_back(BISHOP, BLACK, TileAtPos(1, 6));
	pieces.emplace_back(QUEEN, BLACK, TileAtPos(1, 5));
	pieces.emplace_back(KING, BLACK, TileAtPos(1, 4));
	pieces.emplace_back(BISHOP, BLACK, TileAtPos(1, 3));
	pieces.emplace_back(KNIGHT, BLACK, TileAtPos(1, 2));
	pieces.emplace_back(ROOK, BLACK, TileAtPos(1, 1));

	for (int i = 1; i <= 8; i++)
	{
		pieces.emplace_back(PAWN, BLACK, TileAtPos(2, i));
	}
}




void Board::ChangePiece(Piece* target, TYPE newtype)
{
	target->SetType(newtype);
}

Tile* Board::TileTopLeft(Tile* t)
{
	return TileAtPos(t->row - 1, t->col - 1);
}

Tile* Board::TileTopRight(Tile* t)
{
	return TileAtPos(t->row - 1, t->col + 1);
}

Tile* Board::TileBottomLeft(Tile* t)
{
	return TileAtPos(t->row + 1, t->col - 1);
}

Tile* Board::TileBottomRight(Tile* t)
{
	return TileAtPos(t->row + 1, t->col + 1);
}

Tile* Board::TileTop(Tile* t)
{
	return TileAtPos(t->row - 1, t->col);
}

Tile* Board::TileBottom(Tile* t)
{
	return TileAtPos(t->row + 1, t->col);
}

Tile* Board::TileLeft(Tile* t)
{
	return TileAtPos(t->row, t->col - 1);
}

Tile* Board::TileRight(Tile* t)
{
	return TileAtPos(t->row, t->col + 1);
}

Tile* Board::NextWhiteCapturedTile()
{
	return &whiteCaptured.at(wct_index++);
}

Tile* Board::NextBlackCapturedTile()
{
	return &blackCaptured.at(bct_index++);
}

void Board::Reset()
{
	for (auto& piece : pieces)
	{
		piece.SetTile(piece.StartingTile());
		piece.SetType(piece.StartingType());
		piece.Unkill();
	}
	wct_index = 0;
	bct_index = 0;
}