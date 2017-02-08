#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

#define SPACESHIP_WIDTH 21.0
#define SPACESHIP_HEIGHT 21.0
#define SPACESHIP_COLOR al_map_rgb(0, 255, 0)

struct BlastQueue;
struct AsteroidBelt;

typedef struct Spaceship Spaceship;

Spaceship *createSpaceship();
void destroySpaceship(Spaceship *spaceship);
void drawSpaceship(Spaceship *spaceship);
void updateSpaceship(Spaceship *spaceship);
void updateSpaceshipsBlaster(Spaceship *spaceship, struct BlastQueue *queue);
float spaceshipX(const Spaceship *spaceship);
float spaceshipY(const Spaceship *spaceship);
float spaceshipHeading(const Spaceship *spaceship);
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
int checkSpaceshipAsteroidCollision(Spaceship *spaceship, struct AsteroidBelt *asteroidBelt);
bool isSpaceshipGone(Spaceship *spaceship);

#endif
