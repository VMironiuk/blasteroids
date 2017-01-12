#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

typedef struct Spaceship Spaceship;

struct Spaceship
{
    float x, y;
    float heading;
    float direction;
    float speed;
    ALLEGRO_COLOR color;
};

Spaceship *createSpaceship();
void destroySpaceship(Spaceship *spaceship);
void drawSpaceship(Spaceship *spaceship);
void updateSpaceship(Spaceship *spaceship);
void moveSpaceshipForwardOn();
void moveSpaceshipBackwardOn();
void turnSpaceshipLeftOn();
void turnSpaceshipRightOn();
void moveSpaceshipForwardOff();
void moveSpaceshipBackwardOff();
void turnSpaceshipLeftOff();
void turnSpaceshipRightOff();

#endif
