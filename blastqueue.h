#ifndef BLASTQUEUE_H
#define BLASTQUEUE_H

#include <stdbool.h>

struct Blast;
// struct AsteroidBelt;

typedef struct BlastQueue BlastQueue;

BlastQueue *createBlastQueue();
void destroyBlastQueue(BlastQueue *queue);
void drawBlastQueue(BlastQueue *queue);
void updateBlastQueue(BlastQueue *queue);
void pushBlast(BlastQueue *queue, struct Blast *blast);
void popBlast(BlastQueue *queue);
bool blastQueueHasNext(BlastQueue *queue);
struct Blast *blastQueueNext(BlastQueue *queue);
// int checkBlastAsteroidCollision(BlastQueue *blastQueue, struct AsteroidBelt *asteroidBelt);

#endif
