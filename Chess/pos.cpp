#include "pos.h"

pos::pos(Board* target, TYPE type, TEAM team)
	: board(target), piecetype(type), pieceteam(team)
{
    
}

TYPE pos::PieceType()
{
	return piecetype;
}

TEAM pos::PieceTeam()
{
	return pieceteam;
}

void pos::AddPiece(Piece* p)
{
	pieces.insert(p);
}

void pos::RemovePiece(Piece* p)
{
    if (pieces.find(p) != pieces.end())
    {
        pieces.erase(p);
        Update();
    }
    else
    {
        std::cout << "hello from the pos::RemovePiece function. there is no piece to remove." << '\n';
    }
}

std::unordered_set<Tile*>& pos::GetAttackedTiles()
{
    return attackedTiles;
}

void pos::Update()
{
    //reset bool array
    memset(map, 0, sizeof(map));

    attackedTiles.clear();
	for (Piece* p : pieces)
	{
        if (p->IsDead())
            continue;

        //update bool array
        map[p->CurrentTile()->row - 1][p->CurrentTile()->col - 1] = 1;

        TYPE type = p->Type();
        TEAM team = p->Team();
        Tile* startingtile = p->CurrentTile();
        int row = startingtile->row;
        int col = startingtile->col;

        switch (type)
        {
        case KING:
        {

            for (int it = 0; it < 8; it++) {
                Tile* temp;
                switch (it) {
                case 0:
                    temp = board->TileTopLeft(startingtile);
                    break;
                case 1:
                    temp = board->TileTopRight(startingtile);
                    break;
                case 2:
                    temp = board->TileBottomLeft(startingtile);
                    break;
                case 3:
                    temp = board->TileBottomRight(startingtile);
                    break;
                case 4:
                    temp = board->TileLeft(startingtile);
                    break;
                case 5:
                    temp = board->TileRight(startingtile);
                    break;
                case 6:
                    temp = board->TileBottom(startingtile);
                    break;
                case 7:
                    temp = board->TileTop(startingtile);
                    break;
                default:
                    temp = nullptr;
                    break;
                }
                if (temp != nullptr) 
                {
                    attackedTiles.insert(temp);
                }
            }
            break;
        }
        case PAWN:
        {
            int moveDir = (team == TEAM::WHITE ? -1 : 1);
            int startingRow = (team == WHITE ? board->Rows() - 1 : 2);

            // Check for capturing diagonally
            for (int col_t = col - 1; col_t <= col + 1; col_t += 2) {
                Tile* tt = board->TileAtPos(row + moveDir, col_t);

                if (tt != nullptr) {
                    Piece* p_t = board->PieceAtTile(tt);

                    if (p_t != nullptr && p_t->Team() != team) 
                    {
                        attackedTiles.insert(tt);
                    }
                    else if(p_t == nullptr)
                    {
                        attackedTiles.insert(tt);
                    }
                }
            }
            break;
        }
        case KNIGHT:
        {
            // Possible knight moves
            int r[] = { 2, 2, -2, -2, -1, 1, -1, 1 };
            int c[] = { -1, 1, -1, 1, 2, 2, -2, -2 };

            for (int i = 0; i < 8; i++) {
                Tile* temp = board->TileAtPos(p->CurrentTile()->row + r[i], p->CurrentTile()->col + c[i]);
                if (temp != nullptr) {
                    attackedTiles.insert(temp);
                }
            }
            break;
        }

        case ROOK:
        {
            // Check in all four directions
            for (int dir = 0; dir < 4; dir++) {
                Tile* temp = startingtile;

                while (true) {
                    switch (dir) {
                    case 0:
                        temp = board->TileTop(temp);
                        break;
                    case 1:
                        temp = board->TileRight(temp);
                        break;
                    case 2:
                        temp = board->TileBottom(temp);
                        break;
                    case 3:
                        temp = board->TileLeft(temp);
                        break;
                    default:
                        // No default for you
                        break;
                    }

                    if (temp != nullptr)
                    {
                        Piece* pieceAtTile = board->PieceAtTile(temp);
                        if (pieceAtTile == nullptr)
                        {
                            attackedTiles.insert(temp);
                        }
                        else 
                        {
                            attackedTiles.insert(temp);
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
            }
            break;
        }

        case BISHOP:
        {
            Tile* start = p->CurrentTile();

            // Check in all four diagonal directions
            for (int dir = 0; dir < 4; dir++) {
                Tile* temp = start;

                while (true) {
                    switch (dir) {
                    case 0:
                        temp = board->TileTopLeft(temp);
                        break;
                    case 1:
                        temp = board->TileTopRight(temp);
                        break;
                    case 2:
                        temp = board->TileBottomLeft(temp);
                        break;
                    case 3:
                        temp = board->TileBottomRight(temp);
                        break;
                    default:
                        // No default for you
                        break;
                    }

                    if (temp != nullptr)
                    {
                        Piece* pieceAtTile = board->PieceAtTile(temp);
                        if (pieceAtTile == nullptr)
                        {
                            attackedTiles.insert(temp);
                        }
                        else
                        {
                            attackedTiles.insert(temp);
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
            }
            break;
        }

        case QUEEN:
        {
            Tile* start = p->CurrentTile();

            // Check in all eight possible directions (horizontally, vertically, and diagonally)
            for (int dir = 0; dir < 8; dir++) {
                Tile* temp = start;

                while (true) {
                    switch (dir) {
                    case 0:
                        temp = board->TileTopLeft(temp);
                        break;
                    case 1:
                        temp = board->TileTopRight(temp);
                        break;
                    case 2:
                        temp = board->TileBottomLeft(temp);
                        break;
                    case 3:
                        temp = board->TileBottomRight(temp);
                        break;
                    case 4:
                        temp = board->TileLeft(temp);
                        break;
                    case 5:
                        temp = board->TileRight(temp);
                        break;
                    case 6:
                        temp = board->TileBottom(temp);
                        break;
                    case 7:
                        temp = board->TileTop(temp);
                        break;
                    default:
                        // No default for you
                        break;
                    }

                    if (temp != nullptr)
                    {
                        Piece* pieceAtTile = board->PieceAtTile(temp);
                        if (pieceAtTile == nullptr)
                        {
                            attackedTiles.insert(temp);
                        }
                        else
                        {
                            attackedTiles.insert(temp);
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
            }
            break;
        }

        //switch end
        }
	}
}


void pos::LockIn()
{
    originalPieces.insert(pieces.begin(), pieces.end());
}

void pos::Reset()
{
    pieces.clear();
    pieces.insert(originalPieces.begin(), originalPieces.end());
}