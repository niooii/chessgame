#pragma once

#include "Agent.h"
#include <algorithm>
#include <iostream>
#include <random>

class RandomAgent : public Agent {
public:
    RandomAgent(TEAM agentTeam);

    Move GetMove(std::vector<Move> legalmoves) override;
};