#ifndef BLAST_H
#define BLAST_H

#include "allegro5/allegro.h"

struct Spaceship;
struct BlastQueue;

typedef struct Blast Blast;

Blast *createBlast(const struct Spaceship *spaceship);
void destroyBlast(Blast *blast);
void drawBlast(Blast *blast);
void updateBlast(Blast *blast);
void drawBlastQueue(struct BlastQueue *queue);
void updateBlastQueue(struct BlastQueue *queue);


#endif
