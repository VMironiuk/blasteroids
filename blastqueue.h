#ifndef BLASTQUEUE_H
#define BLASTQUEUE_H

#include <stdbool.h>

struct Blast;

typedef struct BlastQueue BlastQueue;

BlastQueue *create_blast_queue();
void destroy_blast_queue(BlastQueue *queue);
void draw_blast_queue(BlastQueue *queue);
void update_blast_queue(BlastQueue *queue);
void push_blast(BlastQueue *queue, struct Blast *blast);
void pop_blast(BlastQueue *queue);
bool blast_queue_has_next(BlastQueue *queue);
struct Blast *blast_queue_next(BlastQueue *queue);

#endif
