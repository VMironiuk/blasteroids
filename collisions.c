#include "collisions.h"
#include "blastqueue.h"
#include "asteroid.h"
#include "spaceship.h"
#include "blast.h"

int isBoundingBoxCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    return !((x1 > x2 + w2 - 1) || (y1 > y2 + h2 - 1) || (x2 > x1 + w1 - 1) || (y2 > y1 + h1 - 1));
}

int checkBlastAsteroidCollision(BlastQueue *blastQueue, Asteroid *asteroid)
{
    static const int pointsHitting = 100;
    while (blastQueueHasNext(blastQueue)) {
        Blast *currentBlast = blastQueueNext(blastQueue);
        int x1 = blastsX(currentBlast) - blastsWidth() / 2;
        int y1 = blastsY(currentBlast) - blastsHeight() / 2;
        int w1 = blastsWidth();
        int h1 = blastsHeight();
        int x2 = asteroidsX(asteroid) - asteroidsWidth() / 2;
        int y2 = asteroidsY(asteroid) - asteroidsHeight() / 2;
        int w2 = asteroidsWidth();
        int h2 = asteroidsHeight();
        if (isBoundingBoxCollision(x1, y1, w1, h1, x2, y2, w2, h2)) {
            destroyAsteroid(asteroid);
            asteroid = createAsteroid(2.0);
            return pointsHitting;
        }
    }
    return 0;
}

int checkSpaceshipAsteroidCollision(Spaceship *spaceship, Asteroid *asteroid)
{
    return 0;
}
