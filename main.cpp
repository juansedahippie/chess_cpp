#include "game.h"

int main()
{
    float smallest_axis;
    bool flag = true;
    Allegro *allegro = new Allegro(400, 400);
    Game *game = new Game(0, 0, (allegro->getHeight() <= allegro->getWidth()) ? allegro->getHeight() : allegro->getWidth());

    game->draw();
    while (flag)
    {
        switch (allegro->eventHandler())
        {
        case none:
            break;
        case update:
            smallest_axis = (allegro->getHeight() <= allegro->getWidth()) ? allegro->getHeight() : allegro->getWidth();
            game->updateSizeAndPosition(0, 0, smallest_axis);
            game->draw();
            break;
        case left_click:
            if (game->isWithinThis(allegro->getEvent().mouse.x, allegro->getEvent().mouse.y))
            {
                game->clicked(allegro->getEvent().mouse.x, allegro->getEvent().mouse.y);
            }
            game->draw();
            break;
        case right_click:
            break;
        case leave:
            flag = false;
            break;
        }
    }

    delete game;
    delete allegro;

    return 0;
}