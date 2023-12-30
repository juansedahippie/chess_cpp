#ifndef GAMEH
#define GAMEH

#include "square_grid.h"

class Game : public ElementSquareShape
{
private:
    SquareGrid *board;

public:
    Game(float, float, float, const char * = "init_pos.fen");
    ~Game();

    static bool are_board_colors_init;
    static ALLEGRO_COLOR *board_colors;

    void draw(float = 0, float = 0) const override;
    void clicked(float, float);
    void updateSizeAndPosition(float, float, float) override;
};

#endif