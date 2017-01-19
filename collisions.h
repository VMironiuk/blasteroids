#ifndef COLLISIONS_H
#define COLLISIONS_H

struct BlastQueue;
struct Asteroid;
struct Spaceship;

int checkBlastAsteroidCollision(struct BlastQueue *blastQueue, struct Asteroid *asteroid);
int checkSpaceshipAsteroidCollision(struct Spaceship *spaceship, struct Asteroid *asteroid);

#endif
