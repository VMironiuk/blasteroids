#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdbool.h>

#define ASTEROID_WIDTH 25.0
#define ASTEROID_HEIGHT 25.0

typedef struct Asteroid Asteroid;

Asteroid *createAsteroid(float scale);
void breakAsteroid(Asteroid *main, Asteroid **left, Asteroid **right);
void destroyAsteroid(Asteroid *asteroid);
void drawAsteroid(Asteroid *asteroid);
void updateAsteroid(Asteroid *asteroid);
float asteroidX(Asteroid *asteroid);
float asteroidY(Asteroid *asteroid);
bool isAsteroidBroken(Asteroid *asteroid);

#endif
