#include "collisions.h"
#include "blastqueue.h"
#include "asteroidbelt.h"
#include "spaceship.h"
#include "blast.h"
#include "asteroid.h"

int checkBlastAsteroidCollision(BlastQueue *blastQueue, AsteroidBelt *asteroidBelt)
{
    static const int pointsHitting = 100;
    static const int pointsMiss = 0;

    while (blastQueueHasNext(blastQueue)) {
        Blast *currentBlast = blastQueueNext(blastQueue);
        if (isBlastHitToAsteroid(currentBlast, asteroidBelt))
            return pointsHitting;
    }
    
    return pointsMiss;
}

int checkSpaceshipAsteroidCollision(Spaceship *spaceship, AsteroidBelt *asteroidBelt)
{
    static const int saveLive = 0;
    static const int lostLive = 1;

    if (isAsteroidHitToSpaceship(spaceship, asteroidBelt)) {
        setSpaceshipGone(spaceship, true);
        return lostLive;
    }
    return saveLive;
}