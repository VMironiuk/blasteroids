#ifndef ASTEROIDBELT_H
#define ASTEROIDBELT_H

struct Asteroid;
struct Blast;

typedef struct AsteroidBelt AsteroidBelt;

AsteroidBelt *createAsteroidBelt();
void destroyAsteroidBelt(AsteroidBelt *asteroidBelt);
void drawAsteroidBelt(AsteroidBelt *asteroidBelt);
void updateAsteroidBelt(AsteroidBelt *asteroidBelt);
int isBlastHitToAsteroid(struct Blast *blast, AsteroidBelt *asteroidBelt);

#endif
