#include "Game.h"
#include "Piece.h"

Game::Game()
{
    gamestate = IN_PROGRESS;
}

//std::unordered_set<Move> Game::AllLegalMoves(TEAM player)
//{
//	return std::unordered_set<Move>();
//}

std::vector<Move> Game::AllLegalMoves(TEAM player)
{
    std::vector<Piece>& pieces = board.Pieces();
    std::vector<Move> m;
    for (Piece& p : pieces)
    {
        if (p.Team() != player || p.IsDead())
            continue;
        std::vector<Move> t = LegalMoves(&p);
        m.insert(m.end(), t.begin(), t.end());
    }

    //FINDING OUT HOW MANY UNIQUE MOVES
    
    for (Move& move : m)
    {
        bool found{ false };
        for (Move& move_ : uniqueMoves)
        {
            if (move_ == move)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            uniqueMoves.emplace_back(move);
            std::cout << "number of unique moves found: " << uniqueMoves.size() << '\n';
        }
           
    }
    return m;
}

std::vector<Tile*> Game::LegalMoveTiles(Piece* p)
{
    std::vector < Tile* > t;

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
                temp = board.TileTopLeft(startingtile);
                break;
            case 1:
                temp = board.TileTopRight(startingtile);
                break;
            case 2:
                temp = board.TileBottomLeft(startingtile);
                break;
            case 3:
                temp = board.TileBottomRight(startingtile);
                break;
            case 4:
                temp = board.TileLeft(startingtile);
                break;
            case 5:
                temp = board.TileRight(startingtile);
                break;
            case 6:
                temp = board.TileBottom(startingtile);
                break;
            case 7:
                temp = board.TileTop(startingtile);
                break;
            default:
                temp = nullptr;
                break;
            }
            if (temp != nullptr) {
                std::unordered_set<Tile*> DangerTiles = positions.TilesAttackedByTeam(p->Team() == WHITE ? BLACK : WHITE);
                if (DangerTiles.find(temp) == DangerTiles.end()) {
                    Piece* ptemp = board.PieceAtTile(temp);
                    if (ptemp == nullptr) {
                        if (!IsCheckedAfterMove(p, temp)) {
                            t.emplace_back(temp);
                        }
                    }
                    else if (ptemp->Team() != (p->Team() == WHITE ? WHITE : BLACK)) {
                        if (!IsCheckedAfterMove(p, temp)) {
                            t.emplace_back(temp);
                        }
                    }
                }
            }
        }
        break;
    }
	case PAWN:
    {
        int moveDir = (team == TEAM::WHITE ? -1 : 1);
        int startingRow = (team == WHITE ? board.Rows() - 1 : 2);

        // Check for moving two squares forward
        if (row == startingRow) {
            Tile* twoAway = board.TileAtPos(row + 2 * moveDir, col);
            Tile* oneAway = board.TileAtPos(row + moveDir, col);

            if (twoAway != nullptr && board.PieceAtTile(twoAway) == nullptr &&
                board.PieceAtTile(oneAway) == nullptr) {

                if (!IsCheckedAfterMove(p, twoAway)) {
                    t.emplace_back(twoAway);
                }
            }
        }

        // Check for moving one square forward
        Tile* oneForward = board.TileAtPos(row + moveDir, col);
        if (oneForward != nullptr && board.PieceAtTile(oneForward) == nullptr) {
            if (!IsCheckedAfterMove(p, oneForward)) {
                t.emplace_back(oneForward);
            }
        }

        // Check for capturing diagonally
        for (int col_t = col - 1; col_t <= col + 1; col_t += 2) {
            Tile* tt = board.TileAtPos(row + moveDir, col_t);

            if (tt != nullptr) {
                Piece* p_t = board.PieceAtTile(tt);

                if (p_t != nullptr && p_t->Team() != team) {
                    if (!IsCheckedAfterMove(p, tt)) {
                        t.emplace_back(tt);
                    }
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
            Tile* temp = board.TileAtPos(p->CurrentTile()->row + r[i], p->CurrentTile()->col + c[i]);
            if (temp != nullptr) {
                Piece* pieceAtTile = board.PieceAtTile(temp);
                if (pieceAtTile == nullptr) {
                    if (!IsCheckedAfterMove(p, temp)) {
                        t.emplace_back(temp);
                    }
                    continue;
                }
                if (pieceAtTile->Team() != (p->Team() == WHITE ? WHITE : BLACK)) {
                    if (!IsCheckedAfterMove(p, temp)) {
                        t.emplace_back(temp);
                    }
                }
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
                    temp = board.TileTop(temp);
                    break;
                case 1:
                    temp = board.TileRight(temp);
                    break;
                case 2:
                    temp = board.TileBottom(temp);
                    break;
                case 3:
                    temp = board.TileLeft(temp);
                    break;
                default:
                    // No default for you
                    break;
                }

                if (temp != nullptr) {
                    Piece* pieceAtTile = board.PieceAtTile(temp);
                    if (pieceAtTile == nullptr) {
                        if (!IsCheckedAfterMove(p, temp)) {
                            t.emplace_back(temp);
                        }
                    }
                    else {
                        if (pieceAtTile->Team() != p->Team()) {
                            if (!IsCheckedAfterMove(p, temp)) {
                                t.emplace_back(temp);
                            }
                        }
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
        // Check in all four diagonal directions
        for (int dir = 0; dir < 4; dir++) {
            Tile* temp = startingtile;

            while (true) {
                switch (dir) {
                case 0:
                    temp = board.TileTopLeft(temp);
                    break;
                case 1:
                    temp = board.TileTopRight(temp);
                    break;
                case 2:
                    temp = board.TileBottomLeft(temp);
                    break;
                case 3:
                    temp = board.TileBottomRight(temp);
                    break;
                default:
                    // No default for you
                    break;
                }

                if (temp != nullptr) {
                    Piece* pieceAtTile = board.PieceAtTile(temp);
                    if (pieceAtTile == nullptr) {
                        if (!IsCheckedAfterMove(p, temp)) {
                            t.emplace_back(temp);
                        }
                    }
                    else {
                        if (pieceAtTile->Team() != p->Team()) {
                            if (!IsCheckedAfterMove(p, temp)) {
                                t.emplace_back(temp);
                            }
                        }
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

        // Check in all eight possible directions (horizontally, vertically, and diagonally)
        for (int dir = 0; dir < 8; dir++) {
            Tile* temp = startingtile;

            while (true) {
                switch (dir) {
                case 0:
                    temp = board.TileTopLeft(temp);
                    break;
                case 1:
                    temp = board.TileTopRight(temp);
                    break;
                case 2:
                    temp = board.TileBottomLeft(temp);
                    break;
                case 3:
                    temp = board.TileBottomRight(temp);
                    break;
                case 4:
                    temp = board.TileLeft(temp);
                    break;
                case 5:
                    temp = board.TileRight(temp);
                    break;
                case 6:
                    temp = board.TileBottom(temp);
                    break;
                case 7:
                    temp = board.TileTop(temp);
                    break;
                default:
                    // No default for you
                    break;
                }

                if (temp != nullptr) {
                    Piece* pieceAtTile = board.PieceAtTile(temp);
                    if (pieceAtTile == nullptr) {
                        if (!IsCheckedAfterMove(p, temp)) {
                            t.emplace_back(temp);
                        }
                    }
                    else {
                        if (pieceAtTile->Team() != p->Team()) {
                            if (!IsCheckedAfterMove(p, temp)) {
                                t.emplace_back(temp);
                            }
                        }
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

    return t;
}

std::vector<Move> Game::LegalMoves(Piece* p)
{
    std::vector <Move> t;

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
                temp = board.TileTopLeft(startingtile);
                break;
            case 1:
                temp = board.TileTopRight(startingtile);
                break;
            case 2:
                temp = board.TileBottomLeft(startingtile);
                break;
            case 3:
                temp = board.TileBottomRight(startingtile);
                break;
            case 4:
                temp = board.TileLeft(startingtile);
                break;
            case 5:
                temp = board.TileRight(startingtile);
                break;
            case 6:
                temp = board.TileBottom(startingtile);
                break;
            case 7:
                temp = board.TileTop(startingtile);
                break;
            default:
                temp = nullptr;
                break;
            }
            if (temp != nullptr) {
                std::unordered_set<Tile*> DangerTiles = positions.TilesAttackedByTeam(p->Team() == WHITE ? BLACK : WHITE);
                if (DangerTiles.find(temp) == DangerTiles.end()) {
                    Piece* ptemp = board.PieceAtTile(temp);
                    if (ptemp == nullptr) {
                        if (!IsCheckedAfterMove(p, temp)) {
                            t.emplace_back(p, temp, false, p->Type());
                        }
                    }
                    else if (ptemp->Team() != (p->Team() == WHITE ? WHITE : BLACK)) {
                        if (!IsCheckedAfterMove(p, temp)) {
                            t.emplace_back(p, temp, false, p->Type());
                        }
                    }
                }
            }
        }
        break;
    }
    case PAWN:
    {
        int moveDir = (team == TEAM::WHITE ? -1 : 1);
        int startingRow = (team == WHITE ? board.Rows() - 1 : 2);

        bool ispromotion = (row == 2 && team == WHITE) || (row == board.Rows()-1 && team == BLACK);

        // Check for moving two squares forward
        if (row == startingRow) {
            Tile* twoAway = board.TileAtPos(row + 2 * moveDir, col);
            Tile* oneAway = board.TileAtPos(row + moveDir, col);

            if (twoAway != nullptr && board.PieceAtTile(twoAway) == nullptr &&
                board.PieceAtTile(oneAway) == nullptr) {

                if (!IsCheckedAfterMove(p, twoAway)) {
                    if (ispromotion)
                    {
                        t.emplace_back(p, twoAway, true, QUEEN);
                        t.emplace_back(p, twoAway, true, KNIGHT);
                        t.emplace_back(p, twoAway, true, BISHOP);
                        t.emplace_back(p, twoAway, true, ROOK);
                    }
                    else
                    {
                        t.emplace_back(p, twoAway, false, p->Type());
                    }
                }
            }
        }

        // Check for moving one square forward
        Tile* oneForward = board.TileAtPos(row + moveDir, col);
        if (oneForward != nullptr && board.PieceAtTile(oneForward) == nullptr) {
            if (!IsCheckedAfterMove(p, oneForward)) {
                if (ispromotion)
                {
                    t.emplace_back(p, oneForward, true, QUEEN);
                    t.emplace_back(p, oneForward, true, KNIGHT);
                    t.emplace_back(p, oneForward, true, BISHOP);
                    t.emplace_back(p, oneForward, true, ROOK);
                }
                else
                {
                    t.emplace_back(p, oneForward, false, p->Type());
                }
            }
        }

        // Check for capturing diagonally
        for (int col_t = col - 1; col_t <= col + 1; col_t += 2) {
            Tile* tt = board.TileAtPos(row + moveDir, col_t);

            if (tt != nullptr) {
                Piece* p_t = board.PieceAtTile(tt);

                if (p_t != nullptr && p_t->Team() != team) {
                    if (!IsCheckedAfterMove(p, tt)) {
                        if (ispromotion)
                        {
                            t.emplace_back(p, tt, true, QUEEN);
                            t.emplace_back(p, tt, true, KNIGHT);
                            t.emplace_back(p, tt, true, BISHOP);
                            t.emplace_back(p, tt, true, ROOK);
                        }
                        else
                        {
                            t.emplace_back(p, tt, false, p->Type());
                        }
                    }
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
            Tile* temp = board.TileAtPos(p->CurrentTile()->row + r[i], p->CurrentTile()->col + c[i]);
            if (temp != nullptr) {
                Piece* pieceAtTile = board.PieceAtTile(temp);
                if (pieceAtTile == nullptr) {
                    if (!IsCheckedAfterMove(p, temp)) {
                        t.emplace_back(p, temp, false, p->Type());
                    }
                    continue;
                }
                if (pieceAtTile->Team() != (p->Team() == WHITE ? WHITE : BLACK)) {
                    if (!IsCheckedAfterMove(p, temp)) {
                        t.emplace_back(p, temp, false, p->Type());
                    }
                }
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
                    temp = board.TileTop(temp);
                    break;
                case 1:
                    temp = board.TileRight(temp);
                    break;
                case 2:
                    temp = board.TileBottom(temp);
                    break;
                case 3:
                    temp = board.TileLeft(temp);
                    break;
                default:
                    // No default for you
                    break;
                }

                if (temp != nullptr) {
                    Piece* pieceAtTile = board.PieceAtTile(temp);
                    if (pieceAtTile == nullptr) {
                        if (!IsCheckedAfterMove(p, temp)) {
                            t.emplace_back(p, temp, false, p->Type());
                        }
                    }
                    else {
                        if (pieceAtTile->Team() != p->Team()) {
                            if (!IsCheckedAfterMove(p, temp)) {
                                t.emplace_back(p, temp, false, p->Type());
                            }
                        }
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
        // Check in all four diagonal directions
        for (int dir = 0; dir < 4; dir++) {
            Tile* temp = startingtile;

            while (true) {
                switch (dir) {
                case 0:
                    temp = board.TileTopLeft(temp);
                    break;
                case 1:
                    temp = board.TileTopRight(temp);
                    break;
                case 2:
                    temp = board.TileBottomLeft(temp);
                    break;
                case 3:
                    temp = board.TileBottomRight(temp);
                    break;
                default:
                    // No default for you
                    break;
                }

                if (temp != nullptr) {
                    Piece* pieceAtTile = board.PieceAtTile(temp);
                    if (pieceAtTile == nullptr) {
                        if (!IsCheckedAfterMove(p, temp)) {
                            t.emplace_back(p, temp, false, p->Type());
                        }
                    }
                    else {
                        if (pieceAtTile->Team() != p->Team()) {
                            if (!IsCheckedAfterMove(p, temp)) {
                                t.emplace_back(p, temp, false, p->Type());
                            }
                        }
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

        // Check in all eight possible directions (horizontally, vertically, and diagonally)
        for (int dir = 0; dir < 8; dir++) {
            Tile* temp = startingtile;

            while (true) {
                switch (dir) {
                case 0:
                    temp = board.TileTopLeft(temp);
                    break;
                case 1:
                    temp = board.TileTopRight(temp);
                    break;
                case 2:
                    temp = board.TileBottomLeft(temp);
                    break;
                case 3:
                    temp = board.TileBottomRight(temp);
                    break;
                case 4:
                    temp = board.TileLeft(temp);
                    break;
                case 5:
                    temp = board.TileRight(temp);
                    break;
                case 6:
                    temp = board.TileBottom(temp);
                    break;
                case 7:
                    temp = board.TileTop(temp);
                    break;
                default:
                    // No default for you
                    break;
                }

                if (temp != nullptr) {
                    Piece* pieceAtTile = board.PieceAtTile(temp);
                    if (pieceAtTile == nullptr) {
                        if (!IsCheckedAfterMove(p, temp)) {
                            t.emplace_back(p, temp, false, p->Type());
                        }
                    }
                    else {
                        if (pieceAtTile->Team() != p->Team()) {
                            if (!IsCheckedAfterMove(p, temp)) {
                                t.emplace_back(p, temp, false, p->Type());
                            }
                        }
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

    return t;
}

//keep track of moves and revert them if necessary with a function.
//Simulates a move and undos it.
bool Game::IsCheckedAfterMove(Piece* p, Tile* t)
{
    Tile* orgTile = p->CurrentTile();

    Piece* killed = board.PieceAtTile(t);
    Tile* killedOrgTile{};
    if (killed != nullptr)
    {
        //kill the piece
        killedOrgTile = killed->CurrentTile();
        killed->Kill();
        killed->SetTile(board.GarbageTile());
    }

    //this may cause an issue. if there is a problem with piece promotion logic come here!
    //if (p->Type())
    //{
    //    TYPE promotype = QUEEN;
    //    //unimpleneted.
    //    positions.SwitchPiece(p, promotype);
    //    p->SetType(promotype);
    //    positions.Update(promotype, p->Team());
    //}

    //update the piecetypes that the piece had blocked before.
    std::unordered_set<TYPE> worg = positions.TypesAttackingTile(orgTile, WHITE);
    std::unordered_set<TYPE> borg = positions.TypesAttackingTile(orgTile, BLACK);

    std::unordered_set<TYPE> wto = positions.TypesAttackingTile(t, WHITE);
    std::unordered_set<TYPE> bto = positions.TypesAttackingTile(t, BLACK);

    p->SetTile(t);

    positions.Update(p->Type(), p->Team());

    if (killed != nullptr)
    {
        positions.Update(killed->Type(), killed->Team());
    }

    for (TYPE type : worg)
    {
        //std::cout << "found type WHITE " << type << " intersecting tile at " << *orgTile << '\n';
        positions.Update(type, WHITE);
    }
    for (TYPE type : borg)
    {
        //std::cout << "found type BLACK " << type << " intersecting tile at " << *orgTile << '\n';
        positions.Update(type, BLACK);
    }

    for (TYPE type : wto)
    {
        //std::cout << "found type WHITE " << type << " intersecting tile at " << *t << '\n';
        positions.Update(type, WHITE);
    }
    for (TYPE type : bto)
    {
        //std::cout << "found type BLACK " << type << " intersecting tile at " << *t << '\n';
        positions.Update(type, BLACK);
    }


    bool incheck = IsInCheck(p->Team());

    //revert all changes
    p->SetTile(orgTile);

    if (killed != nullptr)
    {
        //unkill the piece
        killed->Unkill();
        killed->SetTile(killedOrgTile);
    }

    positions.Update(p->Type(), p->Team());

    if (killed != nullptr)
    {
        positions.Update(killed->Type(), killed->Team());
    }

    for (TYPE type : worg)
    {
        positions.Update(type, WHITE);
    }
    for (TYPE type : borg)
    {
        positions.Update(type, BLACK);
    }

    for (TYPE type : wto)
    {
        positions.Update(type, WHITE);
    }
    for (TYPE type : bto)
    {
        positions.Update(type, BLACK);
    }

    return incheck;
}

bool Game::IsInCheck(TEAM player)
{
    //find the fucking king
    Piece* k{};
    std::vector<Piece>& pieces = board.Pieces();
    for (Piece& p : pieces)
    {
        if (p.Team() != player)
            continue;

        if (p.Type() == KING)
            k = &p;
    }

    if (k == nullptr)
    {
        std::cout << "there is no king idiot." << '\n';
        return false;
    }

    std::unordered_set<Tile*> DangerTiles = positions.TilesAttackedByTeam(player == WHITE ? BLACK : WHITE);
    return DangerTiles.find(k->CurrentTile()) != DangerTiles.end();
}

Board* Game::GetBoard()
{
	return &board;
}

int Game::DoMove(Move& move)
{
    int pointsreceived{};

    Piece* p = move.moved;
    Tile* orgTile = p->CurrentTile();
    TYPE orgType = p->Type();

    Piece* killed = board.PieceAtTile(move.to);
    if (killed != nullptr)
    {
        //kill the piece
        pointsreceived = killed->Kill();
        killed->SetTile((p->Team() == BLACK ? board.NextWhiteCapturedTile() : board.NextBlackCapturedTile()));
        
    }

    if (move.ispromotion)
    {//move.newtype
        TYPE promotype = move.newtype;
        positions.SwitchPiece(p, promotype);
        p->SetType(promotype);
        positions.Update(promotype, p->Team());
    }

    //update the piecetypes that the piece had blocked before.
    std::unordered_set<TYPE> worg = positions.TypesAttackingTile(orgTile, WHITE);
    std::unordered_set<TYPE> borg = positions.TypesAttackingTile(orgTile, BLACK);

    std::unordered_set<TYPE> wto = positions.TypesAttackingTile(move.to, WHITE);
    std::unordered_set<TYPE> bto = positions.TypesAttackingTile(move.to, BLACK);

    p->SetTile(move.to);

    positions.Update(orgType, p->Team());
    if (killed != nullptr)
        positions.Update(killed->Type(), killed->Team());

    for (TYPE type : worg)
    {
        positions.Update(type, WHITE);
    }
    for (TYPE type : borg)
    {
        positions.Update(type, BLACK);
    }

    for (TYPE type : wto)
    {
        positions.Update(type, WHITE);
    }
    for (TYPE type : bto)
    {
        positions.Update(type, BLACK);
    }

    DoneMoves.push(MoveLog{p, killed, orgTile, move.to, move.ispromotion, orgType, move.newtype});

    //std::cout << "on move: " << DoneMoves.size() << '\n';

    //positions.UpdateAll();
    //af::array a = positions.GetAsTensor();
    return pointsreceived;
}

bool Game::UndoLastMove()
{
    if (DoneMoves.empty())
        return false;
    MoveLog ml = DoneMoves.top();

    Piece* p = ml.moved;

    Piece* killed = ml.killed;
    if (killed != nullptr)
    {
        //unkill the piece
        if (killed->Team() == WHITE)
            board.wct_index--;
        else
            board.bct_index--;
        killed->Unkill();
        killed->SetTile(ml.to);
    }

    if (ml.ispromotion && p != nullptr)
    {
        positions.SwitchPiece(p, ml.originalType);
        p->SetType(ml.originalType);
        positions.Update(ml.originalType, p->Team());
    }

    if(p != nullptr)
        p->SetTile(ml.from);



    //update the piecetypes that the piece had blocked before.
    std::unordered_set<TYPE> worg = positions.TypesAttackingTile(ml.from, WHITE);
    std::unordered_set<TYPE> borg = positions.TypesAttackingTile(ml.from, BLACK);

    std::unordered_set<TYPE> wto = positions.TypesAttackingTile(ml.to, WHITE);
    std::unordered_set<TYPE> bto = positions.TypesAttackingTile(ml.to, BLACK);

    if(p != nullptr)
        positions.Update(p->Type(), p->Team());
    if(killed != nullptr)
        positions.Update(killed->Type(), killed->Team());

    for (TYPE type : worg)
    {
        positions.Update(type, WHITE);
    }
    for (TYPE type : borg)
    {
        positions.Update(type, BLACK);
    }

    for (TYPE type : wto)
    {
        positions.Update(type, WHITE);
    }
    for (TYPE type : bto)
    {
        positions.Update(type, BLACK);
    }

    //after finish
    DoneMoves.pop();
    UndoMoves.push(ml);
    return true;
}

//I IDNT DO SHIT WITH THIS FUNCTION
bool Game::RedoLastMove()
{
    if (UndoMoves.empty())
        return false;
    MoveLog ml = UndoMoves.top();

    Move m{ ml.moved, ml.to, ml.ispromotion, ml.newType };

    DoMove(m);

    //after finish
    UndoMoves.pop();
    return true;
}

void Game::SetActivePiece(Piece* p)
{
    UserActivePiece = p;
    UserAvailableMoves = LegalMoveTiles(p);
}

void Game::UnsetActivePiece()
{
    UserActivePiece = nullptr;
    UserAvailableMoves.clear();
}

Piece* Game::GetActivePiece()
{
    return UserActivePiece;
}

std::vector<Tile*>& Game::GetUserAvailableMoves()
{
    return UserAvailableMoves;
}

void Game::InitGame()
{
    board.InitPieces();
    positions.Init(&board);
}

Positions& Game::GetPositionObject()
{
    return positions;
}

void Game::Reset()
{
    while (!DoneMoves.empty())
        DoneMoves.pop();

    while (!UndoMoves.empty())
        UndoMoves.pop();

    board.Reset();
    positions.ResetAll();
    positions.UpdateAll();
    gamestate = IN_PROGRESS;
}

void Game::SetAgents(std::shared_ptr<Agent> a1, std::shared_ptr<Agent> a2)
{
    agent1 = a1;
    agent2 = a2;
}

int Game::Agent1Move()
{
    Move m = agent1->GetMove(AllLegalMoves(agent1->Team()));
    int points{};
    if (m.moved == nullptr)
    {
        EndGame();
    }
    else
    {
        points = DoMove(m);
    }

    if (IsStalemate())
    {
        gamestate = STALEMATE;
        return -5;
    }

    return points;
}

int Game::Agent2Move()
{
    Move m = agent2->GetMove(AllLegalMoves(agent2->Team()));
    int points{};
    if (m.moved == nullptr)
    {
        EndGame();
    }
    else
    {
        points = DoMove(m);
    }

    if (IsStalemate())
    {
        gamestate = STALEMATE;
        return -5;
    }

    return points;
}

STATE Game::State()
{
    return gamestate;
}

//this is only called when one side has no legal moves left.
void Game::EndGame() {
    if (IsInCheck(WHITE))
    {
        gamestate = WHITE_CHECKMATE;
    }
    else if (IsInCheck(BLACK))
    {
        gamestate = BLACK_CHECKMATE;
    }
    else
    {
        gamestate = STALEMATE;
    }
}

//insufficient material stalemate conditions
bool Game::IsStalemate()
{
    std::vector<Piece*> alive;
    int knights{};
    int bishops{};
    for (Piece& p : board.Pieces())
    {
        if (!p.IsDead())
        {
            alive.emplace_back(&p);
            if (p.Type() == BISHOP)
                bishops++;
            else if (p.Type() == KNIGHT)
                knights++;
        }
    }
    if (alive.size() == 2)
    {
        return true;
    }
    else if (alive.size() == 3)
    {
        if (knights == 1 || bishops == 1)
            return true;
    }
    return false;
}

void Game::KillPiece(Piece* p)
{
    Tile* orgTile = p->CurrentTile();

    if (p != nullptr)
    {
        //kill the piece
        p->Kill();
        p->SetTile((p->Team() == WHITE ? board.NextWhiteCapturedTile() : board.NextBlackCapturedTile()));
    }

    //update the piecetypes that the piece had blocked before.
    std::unordered_set<TYPE> worg = positions.TypesAttackingTile(orgTile, WHITE);
    std::unordered_set<TYPE> borg = positions.TypesAttackingTile(orgTile, BLACK);

    positions.Update(p->Type(), p->Team());

    for (TYPE type : worg)
    {
        positions.Update(type, WHITE);
    }
    for (TYPE type : borg)
    {
        positions.Update(type, BLACK);
    }

    DoneMoves.push(MoveLog{ nullptr, p, orgTile, orgTile, false, p->Type(), p->Type()});
}

af::array Game::GetPositionsAsTensor()
{
    return positions.GetAsTensor();
}

Observation Game::Step(int stepcount)
{
    std::vector<Observation> observations(stepcount);

    for (int i = 0; i < stepcount; i++)
    {
        Observation obs;
        observations[i] = obs;
    }
    // Create states for two agents
    std::vector<std::vector<float>> next_states(2);
    //next_states[0].resize(observations[0].states[0].size() * frame_skip);
    //next_states[1].resize(observations[0].states[1].size() * frame_skip);
    Agent1Move();
}