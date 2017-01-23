#ifndef ASTEROID_H
#define ASTEROID_H

typedef struct Asteroid Asteroid;

Asteroid *createAsteroid(float scale);
void makeAsteroidPartition(Asteroid *main, Asteroid *left, Asteroid *right);
void destroyAsteroid(Asteroid *asteroid);
void drawAsteroid(Asteroid *asteroid);
void updateAsteroid(Asteroid *asteroid);
float asteroidsX(Asteroid *asteroid);
float asteroidsY(Asteroid *asteroid);
float asteroidsWidth();
float asteroidsHeight();
int isAsteroidPartitioned(Asteroid *asteroid);

#endif
