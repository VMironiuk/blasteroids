#include "spaceship.h"

#include <allegro5/allegro_primitives.h>

Spaceship *createSpaceship(ALLEGRO_DISPLAY_MODE *adm)
{
    Spaceship *spaceship = (Spaceship *)malloc(sizeof(Spaceship));
    spaceship->x = adm->width / 2;
    spaceship->y = adm->height / 2;
    spaceship->heading = 0.0;
    spaceship->color = al_map_rgb(0, 255, 0);
    return spaceship;
}

void destroySpaceship(Spaceship *spaceship)
{
    free(spaceship);
}

void drawSpaceship(Spaceship *spaceship)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform, spaceship->x, spaceship->y);
    al_translate_transform(&transform, -spaceship->x, -spaceship->y);
    al_rotate_transform(&transform, spaceship->heading);
    al_translate_transform(&transform, spaceship->x, spaceship->y);
    al_use_transform(&transform);
    al_draw_line(-8, 9, 0, -11, spaceship->color, 3.0f);
    al_draw_line(0, -11, 8, 9, spaceship->color, 3.0f);
    al_draw_line(-6, 4, -1, 4, spaceship->color, 3.0f);
    al_draw_line(6, 4, 1, 4, spaceship->color, 3.0f);
}
