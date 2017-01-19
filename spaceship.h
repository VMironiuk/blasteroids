#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

struct BlastQueue;

typedef struct Spaceship Spaceship;

Spaceship *createSpaceship();
void destroySpaceship(Spaceship *spaceship);
void drawSpaceship(Spaceship *spaceship);
void updateSpaceship(Spaceship *spaceship);
void updateSpaceshipsBlaster(Spaceship *spaceship, struct BlastQueue *queue);
float spaceshipsX(const Spaceship *spaceship);
float spaceshipsY(const Spaceship *spaceship);
float spaceshipsHeading(const Spaceship *spaceship);
ALLEGRO_COLOR spaceshipsColor(const Spaceship *spaceship);
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
