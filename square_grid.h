#ifndef SQUARE_GRIDH
#define SQUARE_GRIDH

#include "square.h"

typedef struct
{
    bool priviledge[2][2];
} castlingStruct;

namespace SquareGridUtils
{
    const uint16_t movement_matrix[8][7] =
        {
            rook  , rook  , rook  , rook  , rook  , rook  , rook  ,
            bishop, knight, none  , none  , none  , none  , none  ,
            knight, bishop, none  , none  , none  , none  , none  ,
            none  , none  , bishop, none  , none  , none  , none  ,
            none  , none  , none  , bishop, none  , none  , none  ,
            none  , none  , none  , none  , bishop, none  , none  ,
            none  , none  , none  , none  , none  , bishop, none  ,
            none  , none  , none  , none  , none  , none  , bishop
        };
}

class SquareGrid : public ElementSquareShape
{
private:
    Square *grid[8][8];
    teams now_turn;           // the team that currently has the right to move
    castlingStruct castling;  // matrix where the rights to castle to a certain side are stored as true - point with team and side
    uint half_moves;          // each move made by a player that isn't a capture or a pawn move - draw at 100
    uint full_moves;          // total number of moves made in the game, increased when black makes a move
    Coord en_passant;         // coordinate of a pawn that is susceptible to en passant
    Coord kings_positions[2]; // position of both kings - point with teams
    Coord last_selected;      // position of the selected square - the piece that you moved was here

    /* Square grid highlights */
    bool highlightGenericPath(Coord &);
    bool highlightKingPath(Coord &);
    bool highlightPawnPath(Coord &);

public:
    SquareGrid(float, float, float, const char *);
    ~SquareGrid();

    void draw(float = 0, float = 0) const override;
    void clicked(float, float);
    void updateSizeAndPosition(float, float, float) override;

    /* Movement validation */
    bool can1stMoveTo2nd(Coord, Coord);
    bool isCheckAgainstThis(teams);
    bool isCheckAgainstOther(teams);
    bool areMovesAvailableForThis(teams);
    bool areMovesAvailableForOther(teams);

    /* Square grid highlights */
    bool highlightPathOfThis(Coord &);
    void clearHighlight();

    /* Movement */
    void genericMoveMade(Coord &, Coord &);
};

#endif