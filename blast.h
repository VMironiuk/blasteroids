#ifndef BLAST_H
#define BLAST_H

#include "allegro5/allegro.h"

struct Spaceship;

typedef struct Blast Blast;

Blast *createBlast(const struct Spaceship *spaceship);
void destroyBlast(Blast *blast);
int isBlastOutOfBoundaries(Blast *blast);
void drawBlast(Blast *blast);
void updateBlast(Blast *blast);
float blastsX(Blast *blast);
float blastsY(Blast *blast);
float blastsWidth();
float blastsHeight();

#endif
