#include "Structs.h"

std::ostream& operator<<(std::ostream& out, Tile t)
{
    return out << "(" << t.row << ", " << t.col << ")";
}

