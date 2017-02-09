#ifndef BLAST_H
#define BLAST_H

#include <allegro5/allegro.h>

#define BLAST_WIDTH 1.0
#define BLAST_HEIGHT 1.0

struct Spaceship;

typedef struct Blast Blast;

Blast *createBlast(const struct Spaceship *spaceship);
void destroyBlast(Blast *blast);
void drawBlast(Blast *blast);
void updateBlast(Blast *blast);
float blastX(Blast *blast);
float blastY(Blast *blast);

#endif
