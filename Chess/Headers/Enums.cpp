#include "Enums.h"

std::ostream& operator<<(std::ostream& out, TYPE type)
{
    switch (type)
    {
    case KING: return out << "KING";
    case QUEEN: return out << "QUEEN";
    case BISHOP: return out << "BISHOP";
    case ROOK: return out << "ROOK";
    case KNIGHT: return out << "KNIGHT";
    case PAWN: return out << "PAWN";
    default: return out << "???";
    }
}

std::ostream& operator<<(std::ostream& out, TEAM team)
{
    switch (team)
    {
    case WHITE: return out << "WHITE";
    case BLACK: return out << "BLACK";
    default: return out << "???";
    }
}

std::ostream& operator<<(std::ostream& out, STATE state)
{
    switch (state)
    {
    case WHITE_CHECKMATE: return out << "WHITE_CHECKMATE";
    case BLACK_CHECKMATE: return out << "BLACK_CHECKMATE";
    case IN_PROGRESS: return out << "IN_PROGRESS";
    case STALEMATE: return out << "STALEMATE";
    case FATAL: return out << "FATAL";
    default: return out << "???";
    }
}