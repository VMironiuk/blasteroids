#include "asteroidbelt.h"
#include "asteroid.h"
#include "blast.h"
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

int isBlastHitToAsteroid(Blast *blast, AsteroidBelt *asteroidBelt)
{
    int row, column;
    for (row = 0; row < ASTEROID_BELT_ROW_COUNT; ++row) {
        for (column = 0; column < ASTEROID_BELT_COLUMN_COUNT; ++column) {
            Asteroid *asteroid = asteroidOf(asteroidBelt, row, column);
            if (asteroid) {
                int x1 = blastsX(blast) - blastsWidth() / 2;
                int y1 = blastsY(blast) - blastsHeight() / 2;
                int w1 = blastsWidth();
                int h1 = blastsHeight();
                int x2 = asteroidsX(asteroid) - asteroidsWidth() / 2;
                int y2 = asteroidsY(asteroid) - asteroidsHeight() / 2;
                int w2 = asteroidsWidth();
                int h2 = asteroidsHeight();
                if (isBoundingBoxCollision(x1, y1, w1, h1, x2, y2, w2, h2)) {
                    if (column == 0 && !isAsteroidPartitioned(asteroid)) {
                        Asteroid *leftAsteroid = 0;
                        Asteroid *rightAsteroid = 0;
                        makeAsteroidPartition(asteroid, leftAsteroid, rightAsteroid);
                        eraseAsteroid(asteroidBelt, row, column);
                        setAsteroid(asteroidBelt, row, column, leftAsteroid);
                        setAsteroid(asteroidBelt, row, ++column, rightAsteroid);
                    } else {
                        eraseAsteroid(asteroidBelt, row, column);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}
