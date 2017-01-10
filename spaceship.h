#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

typedef struct Spaceship Spaceship;

struct Spaceship
{
    float x, y;
    float heading;
    ALLEGRO_COLOR color;
};

Spaceship *createSpaceship(ALLEGRO_DISPLAY_MODE *adm);
void destroySpaceship(Spaceship *spaceship);
void drawSpaceship(Spaceship *spaceship);

#endif
