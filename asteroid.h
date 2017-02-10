#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdbool.h>

#define ASTEROID_WIDTH 25.0
#define ASTEROID_HEIGHT 25.0

typedef struct Asteroid Asteroid;

Asteroid *create_asteroid(float scale);
void break_asteroid(Asteroid *main, Asteroid **left, Asteroid **right);
void destroy_asteroid(Asteroid *asteroid);
void draw_asteroid(Asteroid *asteroid);
void update_asteroid(Asteroid *asteroid);
float asteroid_x(Asteroid *asteroid);
float asteroid_y(Asteroid *asteroid);
bool is_asteroid_broken(Asteroid *asteroid);

#endif
