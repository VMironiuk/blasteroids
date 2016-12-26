#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

typedef struct Spaceship Spaceship;

struct Spaceship
{
    float x, y;
    ALLEGRO_COLOR color;
};

Spaceship *createSpaceship();
void destroySpaceship(Spaceship *spaceship);

#endif