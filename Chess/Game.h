#pragma once

#include <unordered_set>

#include "Board.h" 
#include "Positions.h"
#include "../Agents/Agent.h"
#include <stack>

struct Observation
{
	//af::array 
};

//Class to handle logic (validating moves, calculations etc).
class Game
{
public:
	Game();

	//Returns all available legal moves.
	std::vector<Move> AllLegalMoves(TEAM player);

	//Gets all legal moves for piece, as a tile vector.
	std::vector<Tile*> LegalMoveTiles(Piece* p);

	//Gets all legal moves for piece, as Move structs.
	std::vector<Move> LegalMoves(Piece* p);

	//Simulates a move and returns true if the player's king is checked after the move.
	bool IsCheckedAfterMove(Piece* p, Tile* t);

	//If the team's king is in check.
	bool IsInCheck(TEAM player);

	//Gets board pointer (for initializing the BoardRenderer in GameWindow class).
	Board* GetBoard();

	//Performs move, returns the amount of points if a piece was taken, else returns 0.
	int DoMove(Move& move);

	//Undos the previous move. Returns true if it undo'd something, else returns false.
	bool UndoLastMove();

	//If you undo'd something.
	bool RedoLastMove();

	/*Sets the piece that the user last clicked on (for myself moving stuff around).*/
	void SetActivePiece(Piece* p);

	/*Unsets the piece and kills UserAvailableMoves vector.*/
	void UnsetActivePiece();

	/*Pointer to active piece. Or returns nullptr.*/
	Piece* GetActivePiece();

	/*I dont feel like explaining the names more.*/
	std::vector<Tile*>& GetUserAvailableMoves();

	void InitGame();

	Positions& GetPositionObject();

	//Resets all game shit!
	void Reset();

	void SetAgents(std::shared_ptr<Agent> a1, std::shared_ptr<Agent> a2);

	int Agent1Move();
	int Agent2Move();

	STATE State();

	bool IsStalemate();
	void EndGame();

	//for fun.
	void KillPiece(Piece* p);

	//A 12x8x8 tensor.
	af::array GetPositionsAsTensor();

	//Updates game environment. simulates both agents moving.
	Observation Step(int stepcount);

	//temp delete later igs
	std::vector<Move> uniqueMoves;


private:
	Board board{};

	Positions positions;

	Piece* UserActivePiece{nullptr};
	std::vector<Tile*> UserAvailableMoves;

	std::stack<MoveLog> DoneMoves;
	std::stack<MoveLog> UndoMoves;

	std::shared_ptr<Agent> agent1;
	std::shared_ptr<Agent> agent2;

	STATE gamestate;
};