#ifndef GRIDH
#define GRIDH

#include "allegro.h"
#include "element.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

class Piece
{
private:
    types_sprites sprite;
    types type;
    teams team;

public:
    Piece(char);

    types_sprites getSprite() const;
    types getType() const;
    teams getTeam() const;
};

class Coord
{
public:
    int8_t x;
    int8_t y;

    static Coord none;

    Coord();
    Coord(int8_t, int8_t);

    bool isValid();

    void setCoord(int8_t, int8_t);
    void setCoord(Coord);
    void operator =(Coord);

    bool operator == (Coord &);

    uint8_t distanceTo(Coord &);
};

Coord getCoord(int8_t, int8_t);

class Square : public ElementSquareShape
{
private:
    Piece *piece;
    highlights highlight;

    squareColorsIndex color;
    char *str;

public:
    Square(float, float, float, const char, const uint8_t, const uint8_t);
    ~Square();

    static uint squaresInitialized;
    static ALLEGRO_BITMAP *spritesheet;
    static ALLEGRO_BITMAP **pieces;
    static ALLEGRO_COLOR *square_colors;
    static ALLEGRO_COLOR *highlight_colors;

    void setPiece(Piece *);
    void setHighlight(highlights);

    Piece *getPiece() const;
    highlights getHighlight() const;
    char *getStr() const;

    void draw(float = 0, float = 0) const override;
};

#endif