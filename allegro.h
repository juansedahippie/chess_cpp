#ifndef ALLEGROH
#define ALLEGROH

#include "defines.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

typedef enum
{
    no_event,
    update,
    left_click,
    right_click,
    leave
} events;

class Allegro
{
private:
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_EVENT event;
    float width, height;

public:
    Allegro(float = 800, float = 800);
    ~Allegro();

    float getWidth() const;
    float getHeight() const;

    const ALLEGRO_EVENT &getEvent() const;

    events eventHandler();
};

ALLEGRO_COLOR al_map_rgba(unsigned int);

#endif