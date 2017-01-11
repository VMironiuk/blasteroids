#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

typedef struct Spaceship Spaceship;

struct Spaceship
{
    float x, y;
    float heading;
    float speed;
    ALLEGRO_COLOR color;
};

Spaceship *createSpaceship();
void destroySpaceship(Spaceship *spaceship);
void drawSpaceship(Spaceship *spaceship);
void moveSpaceshipForward(Spaceship *spaceship);
void moveSpaceshipBackward(Spaceship *spaceship);
void turnSpaceshipLeft(Spaceship *spaceship);
void turnSpaceshipRight(Spaceship *spaceship);

#endif
