#include "square_grid.h"

bool SquareGrid::highlightKingPath(Coord &in)
{
    Coord target;
    bool ret = false;
    teams current_team = grid[in.x][in.y]->getPiece()->getTeam();
    teams opposite_team = (current_team == white) ? black : white;

    for (int8_t i = -1; i <= 1; i++)
    {
        for (int8_t j = -1; j <= 1; j++)
        {
            if (i != 0 || j != 0)
            {
                target = getCoord(in.x + i, in.y + j);
                if (target.isValid())
                {
                    if (can1stMoveTo2nd(in, target))
                    {
                        if (target.distanceTo(kings_positions[opposite_team]) > 1)
                        {
                            grid[target.x][target.y]->setHighlight(valid);
                            ret = true;
                        }
                    }
                }
            }
        }
    }

    if (castling.priviledge[kingside][current_team])
    {
        uint8_t row = (current_team == white) ? 7 : 0;
        if (grid[4][row]->getPiece()->getType() == king && grid[7][row]->getPiece()->getType() == rook &&
            grid[4][row]->getPiece()->getTeam() == current_team && grid[7][row]->getPiece()->getTeam() == current_team &&
            can1stMoveTo2nd(getCoord(4, row), getCoord(5, row)) && can1stMoveTo2nd(getCoord(4, row), getCoord(6, row)))
        {
            grid[6][row]->setHighlight(castles);
        }
    }

    if (castling.priviledge[queenside][current_team])
    {
        uint8_t row = (current_team == white) ? 7 : 0;
        if (grid[4][row]->getPiece()->getType() == king && grid[0][row]->getPiece()->getType() == rook &&
            grid[4][row]->getPiece()->getTeam() == current_team && grid[0][row]->getPiece()->getTeam() == current_team &&
            can1stMoveTo2nd(getCoord(4, row), getCoord(1, row)) && can1stMoveTo2nd(getCoord(4, row), getCoord(2, row)) &&
            can1stMoveTo2nd(getCoord(4, row), getCoord(3, row)))
        {
            grid[1][row]->setHighlight(castles);
            grid[2][row]->setHighlight(castles);
        }
    }

    return ret;
}