#include "asteroid.h"

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
    // TODO: add implementation
}

void updateAsteroid(Asteroid *asteroid)
{
    // TODO: add implementation
}
