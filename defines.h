#ifndef DEFINESH
#define DEFINESH

typedef enum : char
{
    white = 0,
    black
} teams;

typedef enum : char
{
    kingside = 0,
    queenside
} sides;

typedef enum : char
{
    none = 0x00,
    king = 0x01,
    queen = 0x04 | 0x10, // bishop or rook
    bishop = 0x04,
    knight = 0x08,
    rook = 0x10,
    pawn = 0x20
} types;

typedef enum : char
{
    w_king = 0,
    w_queen,
    w_bishop,
    w_knight,
    w_rook,
    w_pawn,
    b_king,
    b_queen,
    b_bishop,
    b_knight,
    b_rook,
    b_pawn
} types_sprites;

typedef enum : char
{
    white_square = 0,
    black_square
} squareColorsIndex;

typedef enum : char
{
    background = 0,
    foreground
} boardColorsIndex;

typedef enum : char
{
    blank = -1,
    selected = 0,
    used,
    valid,
    pawn_double,
    pawn_promotes,
    passant,
    castles
} highlights;

#endif