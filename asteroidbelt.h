#ifndef ASTEROIDBELT_H
#define ASTEROIDBELT_H

#include <stdbool.h>

struct Asteroid;
struct Blast;
struct Spaceship;

typedef struct AsteroidBelt AsteroidBelt;

AsteroidBelt *create_asteroid_belt();
void destroy_asteroid_belt(AsteroidBelt *asteroid_belt);
void draw_asteroid_belt(AsteroidBelt *asteroid_belt);
void update_asteroid_belt(AsteroidBelt *asteroid_belt);
bool is_blast_hit_to_asteroid(AsteroidBelt *asteroid_belt, struct Blast *blast);
bool is_asteroid_hit_to_spaceship(AsteroidBelt *asteroid_belt, struct Spaceship *spaceship);

#endif
