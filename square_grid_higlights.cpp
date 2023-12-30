#include "square_grid.h"

bool SquareGrid::highlightGenericPath(Coord &in)
{
    Coord target;
    bool ret = false;

    for (int8_t dir = 0; dir < 4; dir++)
    {
        int16_t this_type = grid[in.x][in.y]->getPiece()->getType();
        int16_t this_team = grid[in.x][in.y]->getPiece()->getTeam();

        for (int8_t i = 0; i < 8; i++)
        {
            for (int8_t j = 0; j < 7; j++)
            {
                switch (dir)
                {
                case 0:
                    target = getCoord(in.x + i, in.y + j + 1);
                    break;
                case 1:
                    target = getCoord(in.x - j - 1, in.y + i);
                    break;
                case 2:
                    target = getCoord(in.x - i, in.y - j - 1);
                    break;
                case 3:
                    target = getCoord(in.x + j + 1, in.y - i);
                    break;
                }

                if (target.isValid())
                {
                    if (SquareGridUtils::movement_matrix[i][j] & this_type)
                    {
                        if (grid[target.x][target.y]->getPiece() == nullptr)
                        {
                            if (can1stMoveTo2nd(in, target))
                            {
                                grid[target.x][target.y]->setHighlight(valid);
                                ret = true;
                            }
                        }
                        else
                        {
                            if (grid[target.x][target.y]->getPiece()->getTeam() != this_team)
                            {
                                if (can1stMoveTo2nd(in, target)) 
                                {
                                    grid[target.x][target.y]->setHighlight(valid);
                                    ret = true;
                                }
                            }
                            if (SquareGridUtils::movement_matrix[i][j] & bishop)
                            {
                                this_type &= ~(bishop);
                            }
                            if (SquareGridUtils::movement_matrix[i][j] & rook)
                            {
                                this_type &= ~(rook);
                            }
                        }
                    }
                }

                if (this_type == 0)
                {
                    j = 8;
                    i = 8;
                }
            }
        }
    }

    return ret;
}

bool SquareGrid::highlightPathOfThis(Coord &in)
{
    bool ret;
    
    if (grid[in.x][in.y]->getPiece() != nullptr)
    {
        switch (grid[in.x][in.y]->getPiece()->getType())
        {
        case king:
            ret = highlightKingPath(in);
            break;
        case queen:
        case bishop:
        case knight:
        case rook:
            ret = highlightGenericPath(in);
            break;
        case pawn:
            ret = highlightPawnPath(in);
            break;
        default:
            break;
        }
    }

    return ret;
}

void SquareGrid::clearHighlight()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            grid[i][j]->setHighlight(blank);
        }
    }
}