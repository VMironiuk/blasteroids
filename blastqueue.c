#include "blastqueue.h"
#include "blast.h"

#include <assert.h>

typedef struct Node Node;

struct Node
{
    Blast *blast;
    Node *next;
};
typedef Node *Link;

struct BlastQueue
{
    Link head;
    Link tail;
    Link current;
};

BlastQueue *createBlastQueue()
{
    BlastQueue *queue = (BlastQueue *)malloc(sizeof *queue);

    assert(queue);

    queue->head = 0;
    queue->tail = 0;
    queue->current = 0;
    return queue;
}

void destroyBlastQueue(BlastQueue *queue)
{
    while (queue->head) {
	free(queue->head->blast);
	Link temp = queue->head;
	queue->head = queue->head->next;
	free(temp);
    }

    free(queue);
}

void pushBlast(BlastQueue *queue, Blast *blast)
{
    Link temp = (Node *)malloc(sizeof *temp);
    temp->blast = blast;
    temp->next = 0;

    if (!queue->tail) {
	queue->head = queue->tail = queue->current = temp;
    } else {
	queue->tail->next = temp;
	queue->tail = temp;
    }
}

void popBlast(BlastQueue *queue)
{
    if (!queue->head)
        return;

    Link temp = queue->head;
    queue->head = queue->head->next;
    free(temp->blast);
    free(temp);

    if (!queue->head)
        queue->tail = queue->current = 0;
}

int blastQueueHasNext(BlastQueue *queue)
{
    int result = (queue->current != 0);
    if (!result)
        queue->current = queue->head;
    return result;
}

Blast *blastQueueNext(BlastQueue *queue)
{
    Blast *blast = queue->current->blast;
    queue->current = queue->current->next;
    return blast;
}

void drawBlastQueue(BlastQueue *queue)
{
    while (blastQueueHasNext(queue))
        drawBlast(blastQueueNext(queue));
}

void updateBlastQueue(BlastQueue *queue)
{
    while (blastQueueHasNext(queue)) {
        Blast *blast = blastQueueNext(queue);
        if (isBlastOutOfBoundaries(blast))
            popBlast(queue);
        else
            updateBlast(blast);
    }
}
