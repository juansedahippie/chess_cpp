#include "square.h"

uint Square::squaresInitialized = 0;
ALLEGRO_BITMAP *Square::spritesheet;
ALLEGRO_BITMAP **Square::pieces;
ALLEGRO_COLOR *Square::square_colors;
ALLEGRO_COLOR *Square::highlight_colors;

Piece::Piece(char c)
{
    switch (c)
    {
    case 'K':
        type = king;
        team = white;
        sprite = w_king;
        break;
    case 'Q':
        type = queen;
        team = white;
        sprite = w_queen;
        break;
    case 'B':
        type = bishop;
        team = white;
        sprite = w_bishop;
        break;
    case 'N':
        type = knight;
        team = white;
        sprite = w_knight;
        break;
    case 'R':
        type = rook;
        team = white;
        sprite = w_rook;
        break;
    case 'P':
        type = pawn;
        team = white;
        sprite = w_pawn;
        break;
    case 'k':
        type = king;
        team = black;
        sprite = b_king;
        break;
    case 'q':
        type = queen;
        team = black;
        sprite = b_queen;
        break;
    case 'b':
        type = bishop;
        team = black;
        sprite = b_bishop;
        break;
    case 'n':
        type = knight;
        team = black;
        sprite = b_knight;
        break;
    case 'r':
        type = rook;
        team = black;
        sprite = b_rook;
        break;
    case 'p':
        type = pawn;
        team = black;
        sprite = b_pawn;
        break;
    }
}

types_sprites Piece::getSprite() const { return sprite; }
types Piece::getType() const { return type; }
teams Piece::getTeam() const { return team; }

Coord Coord::none(-1, -1);

Coord::Coord()
{
}

Coord::Coord(int8_t x_in, int8_t y_in)
{
    x = x_in;
    y = y_in;
}

bool Coord::isValid() { return (x >= 0 && x <= 7 && y >= 0 && y <= 7); }

void Coord::setCoord(int8_t x_in, int8_t y_in)
{
    x = x_in;
    y = y_in;
}

void Coord::setCoord(Coord in)
{
    setCoord(in.x, in.y);
}

void Coord::operator=(Coord in)
{
    this->setCoord(in);
}

bool Coord::operator==(Coord &in)
{
    return (this->x == in.x && this->y == in.y);
}

Coord getCoord(int8_t x_in, int8_t y_in)
{
    Coord ret(x_in, y_in);
    return ret;
}

uint8_t Coord::distanceTo(Coord &in)
{
    int8_t dif_x = this->x - in.x;
    int8_t dif_y = this->y - in.y;
    dif_x *= (dif_x < 0) ? -1 : 1;
    dif_y *= (dif_y < 0) ? -1 : 1;
    return (uint8_t)((dif_x > dif_y) ? dif_x : dif_y);
}

Square::Square(float x_in, float y_in, float w_in, const char c, const uint8_t i, const uint8_t j) : ElementSquareShape(x_in, y_in, w_in)
{
    if (!squaresInitialized)
    {
        spritesheet = al_load_bitmap("images/pieces.png");
        pieces = new ALLEGRO_BITMAP *[12];

        for (uint8_t i = 0; i < 12; i++)
        {
            *(pieces + i) = al_create_sub_bitmap(spritesheet, 200 * (i % 6), 200 * (i >= 6 ? 1 : 0), 200, 200);
        }

        square_colors = new ALLEGRO_COLOR[2];
        square_colors[white_square] = al_map_rgba(0xC8C8C8FF);
        square_colors[black_square] = al_map_rgba(0x323296FF);

        highlight_colors = new ALLEGRO_COLOR[7];
        highlight_colors[selected] = al_map_rgba(0xFF3232AF);
        highlight_colors[used] = al_map_rgba(0xFF3232AF);
        highlight_colors[valid] = al_map_rgba(0xC89600AF);
        highlight_colors[pawn_double] = al_map_rgba(0xC89600AF);
        highlight_colors[pawn_promotes] = al_map_rgba(0xC89600AF);
        highlight_colors[passant] = al_map_rgba(0xC89600AF);
        highlight_colors[castles] = al_map_rgba(0x6EEB5FAF);
    }

    squaresInitialized++;

    if (isalpha(c))
        piece = new Piece(c);
    else
        piece = nullptr;

    color = ((i + j) % 2 == 0) ? white_square : black_square;
    highlight = blank;
    str = new char[3];
    str[0] = i + 'a';
    str[1] = 7 - j + '1';
    str[2] = '\0';
}

Square::~Square()
{
    delete piece;
    delete[] str;

    squaresInitialized--;
    if (!squaresInitialized)
    {
        for (uint8_t i = 0; i < 12; i++)
        {
            al_destroy_bitmap(*(pieces + i));
        }
        al_destroy_bitmap(spritesheet);

        delete[] pieces;
        delete[] square_colors;
        delete[] highlight_colors;
    }
}

void Square::setPiece(Piece *p) { piece = p; }
void Square::setHighlight(highlights h) { highlight = h; }

Piece *Square::getPiece() const { return piece; }
highlights Square::getHighlight() const { return highlight; }
char *Square::getStr() const { return str; }

void Square::draw(float x_origin, float y_origin) const
{
    al_draw_filled_rectangle(x_origin + x, y_origin + y, x_origin + x + w, y_origin + y + w, square_colors[color]);
    if (highlight != blank)
    {
        al_draw_filled_rectangle(x_origin + x, y_origin + y, x_origin + x + w, y_origin + y + w, highlight_colors[highlight]);
    }
    if (piece != nullptr)
    {
        al_draw_scaled_bitmap(pieces[piece->getSprite()], 0, 0, 200, 200, x_origin + x, y_origin + y, w, w, 0);
    }
}