#ifndef COLLISIONS_H
#define COLLISIONS_H

struct Spaceship;
struct BlastQueue;
struct AsteroidBelt;

int checkBlastAsteroidCollision(struct BlastQueue *blastQueue, struct AsteroidBelt *asteroidBelt);
int checkSpaceshipAsteroidCollision(struct Spaceship *spaceship, struct AsteroidBelt *asteroidBelt);

#endif