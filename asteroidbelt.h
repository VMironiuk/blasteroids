#ifndef ASTEROIDBELT_H
#define ASTEROIDBELT_H

#include <stdbool.h>

struct Asteroid;
struct Blast;
struct Spaceship;

typedef struct AsteroidBelt AsteroidBelt;

AsteroidBelt *createAsteroidBelt();
void destroyAsteroidBelt(AsteroidBelt *asteroidBelt);
void drawAsteroidBelt(AsteroidBelt *asteroidBelt);
void updateAsteroidBelt(AsteroidBelt *asteroidBelt);
// TODO: move to collisions.h
bool isBlastHitToAsteroid(struct Blast *blast, AsteroidBelt *asteroidBelt);
bool isAsteroidHitToSpaceship(struct Spaceship *spaceship, AsteroidBelt *asteroidBelt);

#endif
