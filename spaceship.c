#include "spaceship.h"

Spaceship *createSpaceship()
{
    Spaceship *spaceship = (Spaceship *)malloc(sizeof(Spaceship));
    spaceship->color = al_map_rgb(0, 255, 0);
    return spaceship;
}

void destroySpaceship(Spaceship *spaceship)
{
    free(spaceship);
}