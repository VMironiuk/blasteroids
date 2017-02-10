#ifndef COLLISIONS_H
#define COLLISIONS_H

struct Spaceship;
struct BlastQueue;
struct AsteroidBelt;

int is_bounding_box_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
int check_blast_asteroid_collision(struct BlastQueue *blast_queue, struct AsteroidBelt *asteroid_belt);
int check_spaceship_asteroid_collision(struct Spaceship *spaceship, struct AsteroidBelt *asteroid_belt);

#endif