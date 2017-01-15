#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

struct BlastQueue;

typedef struct Spaceship Spaceship;

struct Spaceship
{
    float x;
    float y;
    float heading;
    float movingDirection;
    float speed;
    ALLEGRO_COLOR color;
};

Spaceship *createSpaceship();
void destroySpaceship(Spaceship *spaceship);
void drawSpaceship(Spaceship *spaceship);
void updateSpaceship(Spaceship *spaceship);
void updateSpaceshipsBlaster(Spaceship *spaceship, struct BlastQueue *queue);
void moveSpaceshipForwardOn();
void moveSpaceshipBackwardOn();
void turnSpaceshipLeftOn();
void turnSpaceshipRightOn();
void moveSpaceshipForwardOff();
void moveSpaceshipBackwardOff();
void turnSpaceshipLeftOff();
void turnSpaceshipRightOff();
void shootSpaceshipOn();
void shootSpaceshipOff();

#endif
