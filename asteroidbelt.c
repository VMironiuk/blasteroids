#include "asteroidbelt.h"
#include "asteroid.h"
#include "global.h"

#include <stdlib.h>
#include <assert.h>

#include <stdio.h>

struct AsteroidBelt
{
    Asteroid *asteroids[ASTEROID_BELT_ROW_COUNT][ASTEROID_BELT_COLUMN_COUNT];
};

void checkRange(int row, int column, const char *message)
{
    if (row < 0
        || column < 0
        || row >= ASTEROID_BELT_ROW_COUNT
        || column >= ASTEROID_BELT_COLUMN_COUNT) {
        error(message);
    }
}

AsteroidBelt *createAsteroidBelt()
{
    AsteroidBelt *ab = (AsteroidBelt *)malloc(sizeof *ab);
    int row;
    for (row = 0; row < ASTEROID_BELT_ROW_COUNT; ++row) {
        printf("create asteroid %i\n", row);
        ab->asteroids[row][0] = createAsteroid(1.0);
        printf("x = %f\n", asteroidsX(ab->asteroids[row][0]));
        printf("y = %f\n", asteroidsY(ab->asteroids[row][0]));
        ab->asteroids[row][1] = 0;
    }
    return ab;
}

void destroyAsteroidBelt(AsteroidBelt *asteroidBelt)
{
    int row, column;
    for (row = 0; row < ASTEROID_BELT_ROW_COUNT; ++row) {
        for (column = 0; column < ASTEROID_BELT_COLUMN_COUNT; ++column) {
            if (asteroidBelt->asteroids[row][column])
                free(asteroidBelt->asteroids[row][column]);
        }
    }
    free(asteroidBelt);
}

void eraseAsteroid(AsteroidBelt *asteroidBelt, int row, int column)
{
    checkRange(row, column, "out of range in eraseAsteroid()");
    free(asteroidBelt->asteroids[row][column]);
    asteroidBelt->asteroids[row][column] = 0;
}

void setAsteroid(AsteroidBelt *asteroidBelt, int row, int column, Asteroid *asteroid)
{
    checkRange(row, column, "out of range in setAsteroid()");
    assert(!asteroidBelt->asteroids[row][column]);
    asteroidBelt->asteroids[row][column] = asteroid;
}

Asteroid *asteroidOf(AsteroidBelt *asteroidBelt, int row, int column)
{
    checkRange(row, column, "out of range in asteroidOf()");
    return asteroidBelt->asteroids[row][column];
}

void drawAsteroidBelt(AsteroidBelt *asteroidBelt)
{
    int row, column;
    for (row = 0; row < ASTEROID_BELT_ROW_COUNT; ++row) {
        for (column = 0; column < ASTEROID_BELT_COLUMN_COUNT; ++column) {
            if (asteroidBelt->asteroids[row][column])
                drawAsteroid(asteroidBelt->asteroids[row][column]);
        }
    }
}

void updateAsteroidBelt(AsteroidBelt *asteroidBelt)
{
    int row, column;
    for (row = 0; row < ASTEROID_BELT_ROW_COUNT; ++row) {
        for (column = 0; column < ASTEROID_BELT_COLUMN_COUNT; ++column) {
            if (asteroidBelt->asteroids[row][column])
                updateAsteroid(asteroidBelt->asteroids[row][column]);
        }
    }
}
