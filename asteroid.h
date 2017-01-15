#ifndef ASTEROID_H
#define ASTEROID_H

typedef struct Asteroid Asteroid;

Asteroid *createAsteroid();
void destroyAsteroid(Asteroid *asteroid);
void drawAsteroid(Asteroid *asteroid);
void updateAsteroid(Asteroid *asteroid);

#endif
