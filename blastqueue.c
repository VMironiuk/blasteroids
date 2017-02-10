#include "blastqueue.h"
#include "blast.h"
#include "asteroidbelt.h"

#include <assert.h>

typedef struct Node Node;

struct Node {
    Blast *blast;
    Node *next;
};
typedef Node *Link;

struct BlastQueue {
    Link head;
    Link tail;
    Link current;
};

bool is_blast_out_of_boundaries(Blast *blast) {
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);
    
    if (blast_y(blast) < 0)
        return true;
    else if (blast_y(blast) > adm.height)
        return true;
    else if (blast_x(blast) < 0)
        return true;
    else if (blast_x(blast) > adm.width)
        return true;
    
    return false;
}

BlastQueue *create_blast_queue() {
    BlastQueue *queue = (BlastQueue *)malloc(sizeof *queue);
    
    assert(queue);
    
    queue->head = 0;
    queue->tail = 0;
    queue->current = 0;
    return queue;
}

void destroy_blast_queue(BlastQueue *queue) {
    while (queue->head)
        pop_blast(queue);

    free(queue);
}

void draw_blast_queue(BlastQueue *queue) {
    while (blast_queue_has_next(queue))
        draw_blast(blast_queue_next(queue));
}

void update_blast_queue(BlastQueue *queue) {
    while (blast_queue_has_next(queue)) {
        Blast *blast = blast_queue_next(queue);
        if (is_blast_out_of_boundaries(blast))
            pop_blast(queue);
        else
            update_blast(blast);
    }
}

void push_blast(BlastQueue *queue, Blast *blast) {
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

void pop_blast(BlastQueue *queue) {
    if (!queue->head)
        return;
    
    Link temp = queue->head;
    queue->head = queue->head->next;
    destroy_blast(temp->blast);
    free(temp);
    
    if (!queue->head)
        queue->tail = queue->current = 0;
}

bool blast_queue_has_next(BlastQueue *queue) {
    bool result = (queue->current != 0);
    if (!result)
        queue->current = queue->head;
    return result;
}

Blast *blast_queue_next(BlastQueue *queue) {
    Blast *blast = queue->current->blast;
    queue->current = queue->current->next;
    return blast;
}