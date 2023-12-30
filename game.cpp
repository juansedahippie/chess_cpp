#include "game.h"

bool Game::are_board_colors_init = false;
ALLEGRO_COLOR *Game::board_colors;

Game::Game(float x_in, float y_in, float w_in, const char *position_file_name) : ElementSquareShape(x_in, y_in, w_in)
{
    if(!are_board_colors_init)
    {
        board_colors = new ALLEGRO_COLOR[2];
        board_colors[0] = al_map_rgba(0xC8C8C8FF);
        board_colors[1] = al_map_rgba(0x323296FF);
        are_board_colors_init = true;
    }
    
    board = new SquareGrid(0, 0, w_in, position_file_name);
}

Game::~Game()
{
    delete board;
    if(are_board_colors_init)
    {
        delete[] board_colors;
        are_board_colors_init = false;
    }
}

void Game::draw(float x_origin, float y_origin) const
{
    al_clear_to_color(board_colors[background]);
    board->draw(x + x_origin, y + y_origin);
    al_flip_display();
}

void Game::clicked(float x_in, float y_in)
{
    if(board->isWithinThis(x_in, y_in))
    {
        board->clicked(x_in, y_in);
    }
}

void Game::updateSizeAndPosition(float x_in, float y_in, float w_in)
{
    updateSize(w_in);
    updatePosition(x_in, y_in);
    board->updateSizeAndPosition(0, 0, w_in);
}