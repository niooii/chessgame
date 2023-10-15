#include "RandomAgent.h"

RandomAgent::RandomAgent(TEAM agentTeam) : Agent(agentTeam)
{
    
}

Move RandomAgent::GetMove(std::vector<Move> legalmoves)
{

    if (legalmoves.empty())
    {
        //        std::cout << "NO LEGAL MOVES" << '\n';
        return { nullptr, nullptr, false, NONE };
    }

    std::uniform_int_distribution<> distribution(0, legalmoves.size() - 1);
    std::random_device rd;
    std::mt19937 gen(rd());
    return legalmoves.at(distribution(gen));
}