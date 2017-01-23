#ifndef BLASTQUEUE_H
#define BLASTQUEUE_H

struct Blast;

typedef struct BlastQueue BlastQueue;

BlastQueue *createBlastQueue();
void destroyBlastQueue(BlastQueue *queue);
void pushBlast(BlastQueue *queue, struct Blast *blast);
void popBlast(BlastQueue *queue);
int blastQueueHasNext(BlastQueue *queue);
struct Blast *blastQueueNext(BlastQueue *queue);
void drawBlastQueue(BlastQueue *queue);
void updateBlastQueue(BlastQueue *queue);

#endif
