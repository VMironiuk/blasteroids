#ifndef BLAST_H
#define BLAST_H

#include <allegro5/allegro.h>

#define BLAST_WIDTH 1.0
#define BLAST_HEIGHT 1.0

struct Spaceship;

typedef struct Blast Blast;

Blast *create_blast(const struct Spaceship *spaceship);
void destroy_blast(Blast *blast);
void draw_blast(Blast *blast);
void update_blast(Blast *blast);
float blast_x(Blast *blast);
float blast_y(Blast *blast);

#endif
