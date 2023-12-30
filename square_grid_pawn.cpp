#include "square_grid.h"

bool SquareGrid::highlightPawnPath(Coord &in)
{
    bool ret = false;
    Coord target;

    teams current_team = grid[in.x][in.y]->getPiece()->getTeam();
    teams opposite_team = (current_team == white) ? black : white;

    if (current_team == white)
    {
        target = getCoord(in.x - 1, in.y - 1);
        if (target.isValid())
        {
            if (grid[target.x][target.y]->getPiece() != nullptr && grid[target.x][target.y]->getPiece()->getTeam() == opposite_team)
            {
                if (can1stMoveTo2nd(in, target))
                {
                    grid[target.x][target.y]->setHighlight((y == 1) ? pawn_promotes : valid);
                    ret = true;
                }
            }
        }
        target = getCoord(in.x + 1, in.y - 1);
        if (target.isValid())
        {
            if (grid[target.x][target.y]->getPiece() != nullptr && grid[target.x][target.y]->getPiece()->getTeam() == opposite_team)
            {
                if (can1stMoveTo2nd(in, target))
                {
                    grid[target.x][target.y]->setHighlight((y == 1) ? pawn_promotes : valid);
                    ret = true;
                }
            }
        }
        target = getCoord(in.x, in.y - 1);
        if (target.isValid())
        {
            if (grid[target.x][target.y]->getPiece() == nullptr)
            {
                if (can1stMoveTo2nd(in, target))
                {
                    grid[target.x][target.y]->setHighlight((y == 1) ? pawn_promotes : valid);
                    ret = true;
                }
            }
        }
        if (in.y == 6) // if y = 6, the y coordinate - 2 will always be valid
        {
            target = getCoord(in.x, in.y - 2);
            // both 5 and 4 y values with the same x must be empty
            if (grid[target.x][target.y]->getPiece() == nullptr && grid[target.x][target.y + 1]->getPiece() == nullptr)
            {
                if (can1stMoveTo2nd(in, target))
                {
                    grid[target.x][target.y]->setHighlight((y == 1) ? pawn_promotes : valid);
                    ret = true;
                }
            }
        }
    }
    else
    {
        target = getCoord(in.x - 1, in.y + 1);
        if (target.isValid())
        {
            if (grid[target.x][target.y]->getPiece() != nullptr && grid[target.x][target.y]->getPiece()->getTeam() == opposite_team)
            {
                if (can1stMoveTo2nd(in, target))
                {
                    grid[target.x][target.y]->setHighlight((y == 1) ? pawn_promotes : valid);
                    ret = true;
                }
            }
        }
        target = getCoord(in.x + 1, in.y + 1);
        if (target.isValid())
        {
            if (grid[target.x][target.y]->getPiece() != nullptr && grid[target.x][target.y]->getPiece()->getTeam() == opposite_team)
            {
                if (can1stMoveTo2nd(in, target))
                {
                    grid[target.x][target.y]->setHighlight((y == 1) ? pawn_promotes : valid);
                    ret = true;
                }
            }
        }
        target = getCoord(in.x, in.y + 1);
        if (target.isValid())
        {
            if (grid[target.x][target.y]->getPiece() == nullptr)
            {
                if (can1stMoveTo2nd(in, target))
                {
                    grid[target.x][target.y]->setHighlight((y == 1) ? pawn_promotes : valid);
                    ret = true;
                }
            }
        }
        if (in.y == 1) // if y = 1, the y coordinate + 2 will always be valid
        {
            target = getCoord(in.x, in.y + 2);
            // both 2 and 3 y values with the same x must be empty
            if (grid[target.x][target.y]->getPiece() == nullptr && grid[target.x][target.y - 1]->getPiece() == nullptr)
            {
                if (can1stMoveTo2nd(in, target))
                {
                    grid[target.x][target.y]->setHighlight((y == 1) ? pawn_promotes : valid);
                    ret = true;
                }
            }
        }
    }

    return ret;
}