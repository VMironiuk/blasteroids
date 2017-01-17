#include "asteroid.h"
#include "global.h"

#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <assert.h>

struct Asteroid
{
    float x;
    float y;
    float heading;
    float twist;
    float speed;
    float rotateVelocity;
    float scale;
    ALLEGRO_COLOR color;
};

void limitBoundariesForAsteroid(Asteroid *asteroid)
{
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);

    if (asteroid->y < 0)
        asteroid->y = adm.height;
    else if (asteroid->y > adm.height)
        asteroid->y = 0;
    else if (asteroid->x < 0)
        asteroid->x = adm.width;
    else if (asteroid->x > adm.width)
        asteroid->x = 0;
}


Asteroid *createAsteroid()
{
    Asteroid *asteroid = (Asteroid *)malloc(sizeof *asteroid);

    assert(asteroid);

    // TODO: init asteroid's fields
    return asteroid;
}

void destroyAsteroid(Asteroid *asteroid)
{
    free(asteroid);
}

void drawAsteroid(Asteroid *asteroid)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, degreesToRadians(90.0) - asteroid->heading);
    al_translate_transform(&transform, asteroid->x, asteroid->y);
    al_use_transform(&transform);
    al_draw_line(-20, 20, -25, 5, asteroid->color, 2.0f);
    al_draw_line(-25, 5, -25, -10, asteroid->color, 2.0f);
    al_draw_line(-25, -10, -5, -10, asteroid->color, 2.0f);
    al_draw_line(-5, -10, -10, -20, asteroid->color, 2.0f);
    al_draw_line(-10, -20, 5, -20, asteroid->color, 2.0f);
    al_draw_line(5, -20, 20, -10, asteroid->color, 2.0f);
    al_draw_line(20, -10, 20, -5, asteroid->color, 2.0f);
    al_draw_line(20, -5, 0, 0, asteroid->color, 2.0f);
    al_draw_line(0, 0, 20, 10, asteroid->color, 2.0f);
    al_draw_line(20, 10, 10, 20, asteroid->color, 2.0f);
    al_draw_line(10, 20, 0, 15, asteroid->color, 2.0f);
    al_draw_line(0, 15, -20, 20, asteroid->color, 2.0f);
}

void updateAsteroid(Asteroid *asteroid)
{
    // TODO: add implementation
}
