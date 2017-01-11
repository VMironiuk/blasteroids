#include "spaceship.h"
#include "global.h"

#include <allegro5/allegro_primitives.h>
#include <math.h>

void handleBoundaries(Spaceship *spaceship)
{
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);

    if (spaceship->y < 0)
	spaceship->y = adm.height;
    else if (spaceship->y > adm.height)
	spaceship->y = 0;
    else if (spaceship->x < 0)
	spaceship->x = adm.width;
    else if (spaceship->x > adm.width)
	spaceship->x = 0;
}

Spaceship *createSpaceship()
{
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);

    Spaceship *spaceship = (Spaceship *)malloc(sizeof(Spaceship));
    spaceship->x = adm.width / 2;
    spaceship->y = adm.height / 2;
    spaceship->heading = degreesToRadians(90.0);
    spaceship->speed = 8.0;
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
    al_rotate_transform(&transform, degreesToRadians(90.0) - spaceship->heading);
    al_translate_transform(&transform, spaceship->x, spaceship->y);
    al_use_transform(&transform);
    al_draw_line(-8, 9, 0, -11, spaceship->color, 3.0f);
    al_draw_line(0, -11, 8, 9, spaceship->color, 3.0f);
    al_draw_line(-6, 4, -1, 4, spaceship->color, 3.0f);
    al_draw_line(6, 4, 1, 4, spaceship->color, 3.0f);
}

void moveSpaceshipForward(Spaceship *spaceship)
{
    handleBoundaries(spaceship);
    spaceship->x += cos(spaceship->heading) * spaceship->speed;
    spaceship->y -= sin(spaceship->heading) * spaceship->speed;
}

void moveSpaceshipBackward(Spaceship *spaceship)
{
    handleBoundaries(spaceship);
    spaceship->x -= cos(spaceship->heading) * spaceship->speed;
    spaceship->y += sin(spaceship->heading) * spaceship->speed;
}

void turnSpaceshipLeft(Spaceship *spaceship)
{
    spaceship->heading += degreesToRadians(5.0);
}

void turnSpaceshipRight(Spaceship *spaceship)
{
    spaceship->heading -= degreesToRadians(5.0);
}
