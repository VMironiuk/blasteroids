#include "asteroid.h"
#include "global.h"

#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

struct Asteroid
{
    float x;
    float y;
    float heading;
    float twist;
    float speed;
    float rotateVelocity;
    float scale;
    int isPartitioned;
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

Asteroid *createAsteroid(float scale)
{
    Asteroid *asteroid = (Asteroid *)malloc(sizeof *asteroid);

    assert(asteroid);

    srand((unsigned)time(0));
    
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);

    asteroid->x = rand() % adm.width;
    asteroid->y = rand() % adm.height;
    asteroid->heading = degreesToRadians(rand() % 360);
    asteroid->twist = degreesToRadians(rand() % 360);
    asteroid->speed = rand() % 5 + 2;
    asteroid->rotateVelocity = degreesToRadians(rand() % 5);
    asteroid->scale = scale;
    asteroid->isPartitioned = 0;
    asteroid->color = al_map_rgb(255, 255, 255);
    return asteroid;
}

void makeAsteroidPartition(Asteroid *main, Asteroid *left, Asteroid *right)
{
    left = createAsteroid(2.0);
    left->heading = main->heading - degreesToRadians(20.0);
    left->x = main->x / main->scale;
    left->y = main->y / main->scale;
    left->isPartitioned = 1;

    right = createAsteroid(2.0);
    right->heading = main->heading - degreesToRadians(20.0);
    right->x = main->x / main->scale;
    right->y = main->y / main->scale;
    right->isPartitioned = 1;
}

void destroyAsteroid(Asteroid *asteroid)
{
    free(asteroid);
}

void drawAsteroid(Asteroid *asteroid)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, asteroid->twist);
    al_translate_transform(&transform, asteroid->x * asteroid->scale, asteroid->y * asteroid->scale);
    al_scale_transform(&transform, 1.0 / asteroid->scale, 1.0 / asteroid->scale);
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
    limitBoundariesForAsteroid(asteroid);

    asteroid->twist += asteroid->rotateVelocity;
    asteroid->x += cos(asteroid->heading) * asteroid->speed;
    asteroid->y += sin(asteroid->heading) * asteroid->speed;
}

float asteroidsX(Asteroid *asteroid)
{
    return asteroid->x;
}

float asteroidsY(Asteroid *asteroid)
{
    return asteroid->y;
}

float asteroidsWidth()
{
    static const float width = 25.0;
    return width;
}

float asteroidsHeight()
{
    return asteroidsWidth();
}

int isAsteroidPartitioned(Asteroid *asteroid)
{
    return asteroid->isPartitioned;
}
