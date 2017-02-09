#include "blastqueue.h"
#include "blast.h"
#include "asteroidbelt.h"

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

bool isBlastOutOfBoundaries(Blast *blast)
{
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);
    
    if (blastY(blast) < 0)
        return true;
    else if (blastY(blast) > adm.height)
        return true;
    else if (blastX(blast) < 0)
        return true;
    else if (blastX(blast) > adm.width)
        return true;
    
    return false;
}

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
    while (queue->head)
        popBlast(queue);

    free(queue);
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

bool blastQueueHasNext(BlastQueue *queue)
{
    bool result = (queue->current != 0);
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

// int checkBlastAsteroidCollision(BlastQueue *blastQueue, AsteroidBelt *asteroidBelt)
// {
//     static const int pointsHitting = 100;
//     static const int pointsMiss = 0;

//     while (blastQueueHasNext(blastQueue)) {
//         Blast *currentBlast = blastQueueNext(blastQueue);
//         if (isBlastHitToAsteroid(currentBlast, asteroidBelt))
//             return pointsHitting;
//     }
    
//     return pointsMiss;
// }