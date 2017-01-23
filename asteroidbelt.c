#include "asteroidbelt.h"
#include "asteroid.h"

#include <stdlib.h>

struct AsteroidBelt
{
    Asteroid *asteroids[ASTEROID_BELT_ROW_COUNT][ASTEROID_BELT_COLUMN_COUNT];
};

AsteroidBelt *createAsteroidBelt()
{
    AsteroidBelt *ab = (AsteroidBelt *)malloc(sizeof *ab);
    // TODO: init 2d array
    return ab;
}

void destroyAsteroidBelt(AsteroidBelt *asteroidBelt)
{
    // TODO: free 2d array
    free(asteroidBelt);
}

void eraseAsteroid(AsteroidBelt *asteroidBelt, int row, int column)
{
    // TODO: add implementation
}

void setAsteroid(AsteroidBelt *asteroidBelt, int row, int column, Asteroid *asteroid)
{
    // TODO: add implementation
}

Asteroid *asteroidOf(AsteroidBelt *asteroidBelt, int row, int column)
{
    // TODO: add implementation
}

void drawAsteroidBelt(AsteroidBelt *asteroidBelt)
{
    // TODO: add implementation
}

void updateAsteroidBelt(AsteroidBelt *asteroidBelt)
{
    // TODO: add implementation
}
