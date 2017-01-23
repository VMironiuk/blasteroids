#ifndef ASTEROIDBELT_H
#define ASTEROIDBELT_H

#define ASTEROID_BELT_ROW_COUNT 5
#define ASTEROID_BELT_COLUMN_COUNT 2

struct Asteroid;

typedef struct AsteroidBelt AsteroidBelt;

AsteroidBelt *createAsteroidBelt();
void destroyAsteroidBelt(AsteroidBelt *asteroidBelt);
void eraseAsteroid(AsteroidBelt *asteroidBelt, int row, int column);
void setAsteroid(AsteroidBelt *asteroidBelt, int row, int column, struct Asteroid *asteroid);
struct Asteroid *asteroidOf(AsteroidBelt *asteroidBelt, int row, int column);
void drawAsteroidBelt(AsteroidBelt *asteroidBelt);
void updateAsteroidBelt(AsteroidBelt *asteroidBelt);

#endif
