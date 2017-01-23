#include "collisions.h"
#include "blastqueue.h"
#include "asteroid.h"
#include "spaceship.h"
#include "blast.h"
#include "asteroidbelt.h"

int isBoundingBoxCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    return !((x1 > x2 + w2 - 1) || (y1 > y2 + h2 - 1) || (x2 > x1 + w1 - 1) || (y2 > y1 + h1 - 1));
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

int checkBlastAsteroidCollision(BlastQueue *blastQueue, AsteroidBelt *asteroidBelt)
{
    static const int pointsHitting = 100;
    while (blastQueueHasNext(blastQueue)) {
        Blast *currentBlast = blastQueueNext(blastQueue);
        if (isBlastHitToAsteroid(currentBlast, asteroidBelt))
            return pointsHitting;
    }

    return 0;
}

int checkSpaceshipAsteroidCollision(Spaceship *spaceship, AsteroidBelt *asteroidBelt)
{
    return 0;
}
