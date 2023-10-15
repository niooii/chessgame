#pragma once

#include "../Chess/Headers/Enums.h"
#include "../Chess/Piece.h"
#include <unordered_set>

class Agent {
public:
    Agent(TEAM AgentTeam) : team(AgentTeam) {};
    TEAM Team() { return team; };
    virtual Move GetMove(std::vector<Move> legalmoves) = 0;

private:
    TEAM team;
};