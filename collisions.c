#include "collisions.h"
#include "blastqueue.h"
#include "asteroidbelt.h"
#include "spaceship.h"
#include "blast.h"
#include "asteroid.h"

int is_bounding_box_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return !((x1 > x2 + w2 - 1) || (y1 > y2 + h2 - 1) || (x2 > x1 + w1 - 1) || (y2 > y1 + h1 - 1));
}

int check_blast_asteroid_collision(BlastQueue *blast_queue, AsteroidBelt *asteroid_belt) {
    static const int points_hitting = 100;
    static const int points_miss = 0;

    while (blast_queue_has_next(blast_queue)) {
        Blast *current_blast = blast_queue_next(blast_queue);
        if (is_blast_hit_to_asteroid(asteroid_belt, current_blast))
            return points_hitting;
    }
    
    return points_miss;
}

int check_spaceship_asteroid_collision(Spaceship *spaceship, AsteroidBelt *asteroid_belt) {
    static const int save_live = 0;
    static const int lost_live = 1;

    if (is_asteroid_hit_to_spaceship(asteroid_belt, spaceship)) {
        set_spaceship_gone(spaceship, true);
        return lost_live;
    }
    return save_live;
}