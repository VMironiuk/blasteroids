#ifndef COLLISIONS_H
#define COLLISIONS_H

struct BlastQueue;
struct AsteroidBelt;
struct Spaceship;

int checkBlastAsteroidCollision(struct BlastQueue *blastQueue, struct AsteroidBelt *asteroidBelt);
int checkSpaceshipAsteroidCollision(struct Spaceship *spaceship, struct AsteroidBelt *asteroidBelt);

#endif
