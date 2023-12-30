#include "allegro.h"

Allegro::Allegro(float w, float h)
{
    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();

    width = w;
    height = h;

    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    display = al_create_display(width, height);

    al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_ARROW);
    al_show_mouse_cursor(display);

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
}

Allegro::~Allegro()
{
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    al_uninstall_mouse();
    al_uninstall_keyboard();
    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
}

float Allegro::getWidth() const { return width; }
float Allegro::getHeight() const { return height; }

const ALLEGRO_EVENT &Allegro::getEvent() const { return event; }

events Allegro::eventHandler()
{
    events ret;
    if (al_get_next_event(queue, &event))
    {
        switch (event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_RESIZE:
            if (al_acknowledge_resize(display))
            {
                al_resize_display(event.display.source, event.display.width, event.display.height);
                width = event.display.width;
                height = event.display.height;
            }
            ret = update;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            switch (event.mouse.button)
            {
            case 1:
                ret = left_click;
                break;
            case 2:
                ret = right_click;
                break;
            default:
                ret = no_event;
                break;
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            ret = leave;
            break;
        }
    }
    else
    {
        ret = no_event;
    }

    return ret;
}

ALLEGRO_COLOR al_map_rgba(unsigned int RGBA)
{
    ALLEGRO_COLOR ret;
    unsigned char R = RGBA >> 24;
    unsigned char G = RGBA >> 16;
    unsigned char B = RGBA >> 8;
    unsigned char A = RGBA >> 0;
    ret = al_map_rgba(R, G, B, A);
    return ret;
}