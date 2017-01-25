#ifndef BLASTQUEUE_H
#define BLASTQUEUE_H

struct Blast;
struct AsteroidBelt;

typedef struct BlastQueue BlastQueue;

BlastQueue *createBlastQueue();
void destroyBlastQueue(BlastQueue *queue);
void pushBlast(BlastQueue *queue, struct Blast *blast);
void popBlast(BlastQueue *queue);
int blastQueueHasNext(BlastQueue *queue);
struct Blast *blastQueueNext(BlastQueue *queue);
void drawBlastQueue(BlastQueue *queue);
void updateBlastQueue(BlastQueue *queue);
int checkBlastAsteroidCollision(BlastQueue *blastQueue, struct AsteroidBelt *asteroidBelt);

#endif
